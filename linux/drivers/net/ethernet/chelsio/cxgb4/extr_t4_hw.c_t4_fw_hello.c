#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct fw_hello_cmd {int /*<<< orphan*/  err_to_clearinit; } ;
struct adapter {int dummy; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;
typedef  enum dev_master { ____Placeholder_dev_master } dev_master ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int DEV_STATE_ERR ; 
 int DEV_STATE_INIT ; 
 int DEV_STATE_UNINIT ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int FW_CMD_HELLO_RETRIES ; 
 int FW_CMD_HELLO_TIMEOUT ; 
 int FW_HELLO_CMD_CLEARINIT_F ; 
 int FW_HELLO_CMD_ERR_F ; 
 int FW_HELLO_CMD_INIT_F ; 
 int FW_HELLO_CMD_MASTERDIS_V (int) ; 
 int FW_HELLO_CMD_MASTERFORCE_V (int) ; 
 int FW_HELLO_CMD_MBASYNCNOT_V (unsigned int) ; 
 unsigned int FW_HELLO_CMD_MBMASTER_G (int) ; 
 unsigned int FW_HELLO_CMD_MBMASTER_M ; 
 int FW_HELLO_CMD_MBMASTER_V (unsigned int) ; 
 int FW_HELLO_CMD_STAGE_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HELLO ; 
 int /*<<< orphan*/  INIT_CMD (struct fw_hello_cmd,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MASTER_CANT ; 
 int MASTER_MUST ; 
 int /*<<< orphan*/  PCIE_FW_A ; 
 int PCIE_FW_ERR_F ; 
 int PCIE_FW_INIT_F ; 
 unsigned int PCIE_FW_MASTER_G (int) ; 
 unsigned int PCIE_FW_MASTER_M ; 
 int PCIE_FW_MASTER_VLD_F ; 
 int /*<<< orphan*/  WRITE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_hello_cmd_stage_os ; 
 int /*<<< orphan*/  memset (struct fw_hello_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_report_fw_error (struct adapter*) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_hello_cmd*,int,struct fw_hello_cmd*) ; 

int t4_fw_hello(struct adapter *adap, unsigned int mbox, unsigned int evt_mbox,
		enum dev_master master, enum dev_state *state)
{
	int ret;
	struct fw_hello_cmd c;
	u32 v;
	unsigned int master_mbox;
	int retries = FW_CMD_HELLO_RETRIES;

retry:
	memset(&c, 0, sizeof(c));
	INIT_CMD(c, HELLO, WRITE);
	c.err_to_clearinit = cpu_to_be32(
		FW_HELLO_CMD_MASTERDIS_V(master == MASTER_CANT) |
		FW_HELLO_CMD_MASTERFORCE_V(master == MASTER_MUST) |
		FW_HELLO_CMD_MBMASTER_V(master == MASTER_MUST ?
					mbox : FW_HELLO_CMD_MBMASTER_M) |
		FW_HELLO_CMD_MBASYNCNOT_V(evt_mbox) |
		FW_HELLO_CMD_STAGE_V(fw_hello_cmd_stage_os) |
		FW_HELLO_CMD_CLEARINIT_F);

	/*
	 * Issue the HELLO command to the firmware.  If it's not successful
	 * but indicates that we got a "busy" or "timeout" condition, retry
	 * the HELLO until we exhaust our retry limit.  If we do exceed our
	 * retry limit, check to see if the firmware left us any error
	 * information and report that if so.
	 */
	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret < 0) {
		if ((ret == -EBUSY || ret == -ETIMEDOUT) && retries-- > 0)
			goto retry;
		if (t4_read_reg(adap, PCIE_FW_A) & PCIE_FW_ERR_F)
			t4_report_fw_error(adap);
		return ret;
	}

	v = be32_to_cpu(c.err_to_clearinit);
	master_mbox = FW_HELLO_CMD_MBMASTER_G(v);
	if (state) {
		if (v & FW_HELLO_CMD_ERR_F)
			*state = DEV_STATE_ERR;
		else if (v & FW_HELLO_CMD_INIT_F)
			*state = DEV_STATE_INIT;
		else
			*state = DEV_STATE_UNINIT;
	}

	/*
	 * If we're not the Master PF then we need to wait around for the
	 * Master PF Driver to finish setting up the adapter.
	 *
	 * Note that we also do this wait if we're a non-Master-capable PF and
	 * there is no current Master PF; a Master PF may show up momentarily
	 * and we wouldn't want to fail pointlessly.  (This can happen when an
	 * OS loads lots of different drivers rapidly at the same time).  In
	 * this case, the Master PF returned by the firmware will be
	 * PCIE_FW_MASTER_M so the test below will work ...
	 */
	if ((v & (FW_HELLO_CMD_ERR_F|FW_HELLO_CMD_INIT_F)) == 0 &&
	    master_mbox != mbox) {
		int waiting = FW_CMD_HELLO_TIMEOUT;

		/*
		 * Wait for the firmware to either indicate an error or
		 * initialized state.  If we see either of these we bail out
		 * and report the issue to the caller.  If we exhaust the
		 * "hello timeout" and we haven't exhausted our retries, try
		 * again.  Otherwise bail with a timeout error.
		 */
		for (;;) {
			u32 pcie_fw;

			msleep(50);
			waiting -= 50;

			/*
			 * If neither Error nor Initialized are indicated
			 * by the firmware keep waiting till we exhaust our
			 * timeout ... and then retry if we haven't exhausted
			 * our retries ...
			 */
			pcie_fw = t4_read_reg(adap, PCIE_FW_A);
			if (!(pcie_fw & (PCIE_FW_ERR_F|PCIE_FW_INIT_F))) {
				if (waiting <= 0) {
					if (retries-- > 0)
						goto retry;

					return -ETIMEDOUT;
				}
				continue;
			}

			/*
			 * We either have an Error or Initialized condition
			 * report errors preferentially.
			 */
			if (state) {
				if (pcie_fw & PCIE_FW_ERR_F)
					*state = DEV_STATE_ERR;
				else if (pcie_fw & PCIE_FW_INIT_F)
					*state = DEV_STATE_INIT;
			}

			/*
			 * If we arrived before a Master PF was selected and
			 * there's not a valid Master PF, grab its identity
			 * for our caller.
			 */
			if (master_mbox == PCIE_FW_MASTER_M &&
			    (pcie_fw & PCIE_FW_MASTER_VLD_F))
				master_mbox = PCIE_FW_MASTER_G(pcie_fw);
			break;
		}
	}

	return master_mbox;
}