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
struct fw_cmd_hdr {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct csio_mbm {struct csio_mb* mcurrent; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int /*<<< orphan*/  pfn; struct csio_mbm mbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_mbm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CMD_OP_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CMD_RETVAL_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_ETIMEDOUT ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_tmo ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

struct csio_mb *
csio_mb_tmo_handler(struct csio_hw *hw)
{
	struct csio_mbm *mbm = &hw->mbm;
	struct csio_mb *mbp =  mbm->mcurrent;
	struct fw_cmd_hdr *fw_hdr;

	/*
	 * Could be a race b/w the completion handler and the timer
	 * and the completion handler won that race.
	 */
	if (mbp == NULL) {
		CSIO_DB_ASSERT(0);
		return NULL;
	}

	fw_hdr = (struct fw_cmd_hdr *)(mbp->mb);

	csio_dbg(hw, "Mailbox num:%x op:0x%x timed out\n", hw->pfn,
		    FW_CMD_OP_G(ntohl(fw_hdr->hi)));

	mbm->mcurrent = NULL;
	CSIO_INC_STATS(mbm, n_tmo);
	fw_hdr->lo = htonl(FW_CMD_RETVAL_V(FW_ETIMEDOUT));

	return mbp;
}