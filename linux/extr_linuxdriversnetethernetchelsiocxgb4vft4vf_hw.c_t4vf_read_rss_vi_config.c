#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ip6fourtupen; int ip6twotupen; int ip4fourtupen; int ip4twotupen; int udpen; int /*<<< orphan*/  defaultq; } ;
union rss_vi_config {TYPE_5__ basicvirtual; } ;
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  defaultq_to_udpen; } ;
struct TYPE_9__ {TYPE_3__ basicvirtual; } ;
struct fw_rss_vi_config_cmd {TYPE_4__ u; void* retval_len16; void* op_to_viid; } ;
struct TYPE_6__ {int mode; } ;
struct TYPE_7__ {TYPE_1__ rss; } ;
struct adapter {TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_rss_vi_config_cmd) ; 
#define  FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL 128 
 int /*<<< orphan*/  FW_RSS_VI_CONFIG_CMD ; 
 int /*<<< orphan*/  FW_RSS_VI_CONFIG_CMD_DEFAULTQ_G (int) ; 
 int FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_UDPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_VIID (unsigned int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_vi_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_rss_vi_config_cmd*,int,struct fw_rss_vi_config_cmd*) ; 

int t4vf_read_rss_vi_config(struct adapter *adapter, unsigned int viid,
			    union rss_vi_config *config)
{
	struct fw_rss_vi_config_cmd cmd, rpl;
	int v;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_READ_F |
				     FW_RSS_VI_CONFIG_CMD_VIID(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &rpl);
	if (v)
		return v;

	switch (adapter->params.rss.mode) {
	case FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: {
		u32 word = be32_to_cpu(rpl.u.basicvirtual.defaultq_to_udpen);

		config->basicvirtual.ip6fourtupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F) != 0);
		config->basicvirtual.ip6twotupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F) != 0);
		config->basicvirtual.ip4fourtupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F) != 0);
		config->basicvirtual.ip4twotupen =
			((word & FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F) != 0);
		config->basicvirtual.udpen =
			((word & FW_RSS_VI_CONFIG_CMD_UDPEN_F) != 0);
		config->basicvirtual.defaultq =
			FW_RSS_VI_CONFIG_CMD_DEFAULTQ_G(word);
		break;
	}

	default:
		return -EINVAL;
	}

	return 0;
}