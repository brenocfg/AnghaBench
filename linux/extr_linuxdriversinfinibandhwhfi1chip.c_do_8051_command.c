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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dc8051_timed_out; int /*<<< orphan*/  dc8051_lock; scalar_t__ dc_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC8051 ; 
 int /*<<< orphan*/  DC8051_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  DC_DC8051_CFG_EXT_DEV_0 ; 
 int DC_DC8051_CFG_EXT_DEV_0_COMPLETED_SMASK ; 
 int DC_DC8051_CFG_EXT_DEV_0_RETURN_CODE_SHIFT ; 
 int DC_DC8051_CFG_EXT_DEV_0_RSP_DATA_SHIFT ; 
 int /*<<< orphan*/  DC_DC8051_CFG_EXT_DEV_1 ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SMASK ; 
 int /*<<< orphan*/  DC_DC8051_CFG_HOST_CMD_0 ; 
 int DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_MASK ; 
 int DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_SHIFT ; 
 int DC_DC8051_CFG_HOST_CMD_0_REQ_NEW_SMASK ; 
 int DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_MASK ; 
 int DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  DC_DC8051_CFG_HOST_CMD_1 ; 
 int DC_DC8051_CFG_HOST_CMD_1_COMPLETED_SMASK ; 
 int DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_MASK ; 
 int DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_SHIFT ; 
 int DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_MASK ; 
 int DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_SHIFT ; 
 int ENODEV ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 scalar_t__ HCMD_READ_LCB_CSR ; 
 scalar_t__ HCMD_WRITE_LCB_CSR ; 
 int /*<<< orphan*/  _dc_shutdown (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  _dc_start (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_8051_command(struct hfi1_devdata *dd, u32 type, u64 in_data,
			   u64 *out_data)
{
	u64 reg, completed;
	int return_code;
	unsigned long timeout;

	hfi1_cdbg(DC8051, "type %d, data 0x%012llx", type, in_data);

	mutex_lock(&dd->dc8051_lock);

	/* We can't send any commands to the 8051 if it's in reset */
	if (dd->dc_shutdown) {
		return_code = -ENODEV;
		goto fail;
	}

	/*
	 * If an 8051 host command timed out previously, then the 8051 is
	 * stuck.
	 *
	 * On first timeout, attempt to reset and restart the entire DC
	 * block (including 8051). (Is this too big of a hammer?)
	 *
	 * If the 8051 times out a second time, the reset did not bring it
	 * back to healthy life. In that case, fail any subsequent commands.
	 */
	if (dd->dc8051_timed_out) {
		if (dd->dc8051_timed_out > 1) {
			dd_dev_err(dd,
				   "Previous 8051 host command timed out, skipping command %u\n",
				   type);
			return_code = -ENXIO;
			goto fail;
		}
		_dc_shutdown(dd);
		_dc_start(dd);
	}

	/*
	 * If there is no timeout, then the 8051 command interface is
	 * waiting for a command.
	 */

	/*
	 * When writing a LCB CSR, out_data contains the full value to
	 * to be written, while in_data contains the relative LCB
	 * address in 7:0.  Do the work here, rather than the caller,
	 * of distrubting the write data to where it needs to go:
	 *
	 * Write data
	 *   39:00 -> in_data[47:8]
	 *   47:40 -> DC8051_CFG_EXT_DEV_0.RETURN_CODE
	 *   63:48 -> DC8051_CFG_EXT_DEV_0.RSP_DATA
	 */
	if (type == HCMD_WRITE_LCB_CSR) {
		in_data |= ((*out_data) & 0xffffffffffull) << 8;
		/* must preserve COMPLETED - it is tied to hardware */
		reg = read_csr(dd, DC_DC8051_CFG_EXT_DEV_0);
		reg &= DC_DC8051_CFG_EXT_DEV_0_COMPLETED_SMASK;
		reg |= ((((*out_data) >> 40) & 0xff) <<
				DC_DC8051_CFG_EXT_DEV_0_RETURN_CODE_SHIFT)
		      | ((((*out_data) >> 48) & 0xffff) <<
				DC_DC8051_CFG_EXT_DEV_0_RSP_DATA_SHIFT);
		write_csr(dd, DC_DC8051_CFG_EXT_DEV_0, reg);
	}

	/*
	 * Do two writes: the first to stabilize the type and req_data, the
	 * second to activate.
	 */
	reg = ((u64)type & DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_MASK)
			<< DC_DC8051_CFG_HOST_CMD_0_REQ_TYPE_SHIFT
		| (in_data & DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_MASK)
			<< DC_DC8051_CFG_HOST_CMD_0_REQ_DATA_SHIFT;
	write_csr(dd, DC_DC8051_CFG_HOST_CMD_0, reg);
	reg |= DC_DC8051_CFG_HOST_CMD_0_REQ_NEW_SMASK;
	write_csr(dd, DC_DC8051_CFG_HOST_CMD_0, reg);

	/* wait for completion, alternate: interrupt */
	timeout = jiffies + msecs_to_jiffies(DC8051_COMMAND_TIMEOUT);
	while (1) {
		reg = read_csr(dd, DC_DC8051_CFG_HOST_CMD_1);
		completed = reg & DC_DC8051_CFG_HOST_CMD_1_COMPLETED_SMASK;
		if (completed)
			break;
		if (time_after(jiffies, timeout)) {
			dd->dc8051_timed_out++;
			dd_dev_err(dd, "8051 host command %u timeout\n", type);
			if (out_data)
				*out_data = 0;
			return_code = -ETIMEDOUT;
			goto fail;
		}
		udelay(2);
	}

	if (out_data) {
		*out_data = (reg >> DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_SHIFT)
				& DC_DC8051_CFG_HOST_CMD_1_RSP_DATA_MASK;
		if (type == HCMD_READ_LCB_CSR) {
			/* top 16 bits are in a different register */
			*out_data |= (read_csr(dd, DC_DC8051_CFG_EXT_DEV_1)
				& DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SMASK)
				<< (48
				    - DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT);
		}
	}
	return_code = (reg >> DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_SHIFT)
				& DC_DC8051_CFG_HOST_CMD_1_RETURN_CODE_MASK;
	dd->dc8051_timed_out = 0;
	/*
	 * Clear command for next user.
	 */
	write_csr(dd, DC_DC8051_CFG_HOST_CMD_0, 0);

fail:
	mutex_unlock(&dd->dc8051_lock);
	return return_code;
}