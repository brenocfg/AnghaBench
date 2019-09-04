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
struct TYPE_5__ {void* synmapen_to_hashtoeplitz; void* mode_pkd; } ;
struct TYPE_4__ {void* mode_pkd; } ;
struct TYPE_6__ {TYPE_2__ basicvirtual; TYPE_1__ manual; } ;
struct fw_rss_glb_config_cmd {TYPE_3__ u; void* retval_len16; void* op_to_write; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_CMD_REQUEST_F ; 
 unsigned int FW_CMD_WRITE_F ; 
 unsigned int FW_LEN16 (struct fw_rss_glb_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_GLB_CONFIG_CMD ; 
 unsigned int FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL ; 
 unsigned int FW_RSS_GLB_CONFIG_CMD_MODE_MANUAL ; 
 unsigned int FW_RSS_GLB_CONFIG_CMD_MODE_V (unsigned int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_glb_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int,struct fw_rss_glb_config_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_glbl_rss(struct adapter *adapter, int mbox, unsigned int mode,
		       unsigned int flags)
{
	struct fw_rss_glb_config_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_write = cpu_to_be32(FW_CMD_OP_V(FW_RSS_GLB_CONFIG_CMD) |
				    FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	if (mode == FW_RSS_GLB_CONFIG_CMD_MODE_MANUAL) {
		c.u.manual.mode_pkd =
			cpu_to_be32(FW_RSS_GLB_CONFIG_CMD_MODE_V(mode));
	} else if (mode == FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL) {
		c.u.basicvirtual.mode_pkd =
			cpu_to_be32(FW_RSS_GLB_CONFIG_CMD_MODE_V(mode));
		c.u.basicvirtual.synmapen_to_hashtoeplitz = cpu_to_be32(flags);
	} else
		return -EINVAL;
	return t4_wr_mbox(adapter, mbox, &c, sizeof(c), NULL);
}