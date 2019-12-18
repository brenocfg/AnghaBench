#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  line; int /*<<< orphan*/  filename_0_7; } ;
struct TYPE_4__ {int /*<<< orphan*/  dprtstrparam3; int /*<<< orphan*/  dprtstrparam2; int /*<<< orphan*/  dprtstrparam1; int /*<<< orphan*/  dprtstrparam0; int /*<<< orphan*/  dprtstridx; } ;
struct TYPE_6__ {TYPE_2__ assert; TYPE_1__ prt; } ;
struct fw_debug_cmd {TYPE_3__ u; int /*<<< orphan*/  op_type; } ;
struct csio_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int FW_DEBUG_CMD_TYPE_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_fatal (struct csio_hw*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,...) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_mb_dump_fw_dbg(struct csio_hw *hw, __be64 *cmd)
{
	struct fw_debug_cmd *dbg = (struct fw_debug_cmd *)cmd;

	if ((FW_DEBUG_CMD_TYPE_G(ntohl(dbg->op_type))) == 1) {
		csio_info(hw, "FW print message:\n");
		csio_info(hw, "\tdebug->dprtstridx = %d\n",
			    ntohs(dbg->u.prt.dprtstridx));
		csio_info(hw, "\tdebug->dprtstrparam0 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam0));
		csio_info(hw, "\tdebug->dprtstrparam1 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam1));
		csio_info(hw, "\tdebug->dprtstrparam2 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam2));
		csio_info(hw, "\tdebug->dprtstrparam3 = 0x%x\n",
			    ntohl(dbg->u.prt.dprtstrparam3));
	} else {
		/* This is a FW assertion */
		csio_fatal(hw, "FW assertion at %.16s:%u, val0 %#x, val1 %#x\n",
			    dbg->u.assert.filename_0_7,
			    ntohl(dbg->u.assert.line),
			    ntohl(dbg->u.assert.x),
			    ntohl(dbg->u.assert.y));
	}
}