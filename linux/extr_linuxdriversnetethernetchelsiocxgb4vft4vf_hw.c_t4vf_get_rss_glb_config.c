#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int synmapen; int syn4tupenipv6; int syn2tupenipv6; int syn4tupenipv4; int syn2tupenipv4; int ofdmapen; int tnlmapen; int tnlalllookup; int hashtoeplitz; } ;
struct TYPE_12__ {TYPE_5__ basicvirtual; } ;
struct rss_params {int mode; TYPE_6__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  synmapen_to_hashtoeplitz; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode_pkd; } ;
struct TYPE_10__ {TYPE_3__ basicvirtual; TYPE_2__ manual; } ;
struct fw_rss_glb_config_cmd {TYPE_4__ u; void* retval_len16; void* op_to_write; } ;
struct TYPE_7__ {struct rss_params rss; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_rss_glb_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_GLB_CONFIG_CMD ; 
 int FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_F ; 
#define  FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL 128 
 int FW_RSS_GLB_CONFIG_CMD_MODE_G (int) ; 
 int FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_F ; 
 int FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_F ; 
 int FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_F ; 
 int FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_F ; 
 int FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_F ; 
 int FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_F ; 
 int FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F ; 
 int FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_glb_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_rss_glb_config_cmd*,int,struct fw_rss_glb_config_cmd*) ; 

int t4vf_get_rss_glb_config(struct adapter *adapter)
{
	struct rss_params *rss = &adapter->params.rss;
	struct fw_rss_glb_config_cmd cmd, rpl;
	int v;

	/*
	 * Execute an RSS Global Configuration read command to retrieve
	 * our RSS configuration.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_write = cpu_to_be32(FW_CMD_OP_V(FW_RSS_GLB_CONFIG_CMD) |
				      FW_CMD_REQUEST_F |
				      FW_CMD_READ_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &rpl);
	if (v)
		return v;

	/*
	 * Transate the big-endian RSS Global Configuration into our
	 * cpu-endian format based on the RSS mode.  We also do first level
	 * filtering at this point to weed out modes which don't support
	 * VF Drivers ...
	 */
	rss->mode = FW_RSS_GLB_CONFIG_CMD_MODE_G(
			be32_to_cpu(rpl.u.manual.mode_pkd));
	switch (rss->mode) {
	case FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: {
		u32 word = be32_to_cpu(
				rpl.u.basicvirtual.synmapen_to_hashtoeplitz);

		rss->u.basicvirtual.synmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_SYNMAPEN_F) != 0);
		rss->u.basicvirtual.syn4tupenipv6 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6_F) != 0);
		rss->u.basicvirtual.syn2tupenipv6 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6_F) != 0);
		rss->u.basicvirtual.syn4tupenipv4 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4_F) != 0);
		rss->u.basicvirtual.syn2tupenipv4 =
			((word & FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4_F) != 0);

		rss->u.basicvirtual.ofdmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_OFDMAPEN_F) != 0);

		rss->u.basicvirtual.tnlmapen =
			((word & FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F) != 0);
		rss->u.basicvirtual.tnlalllookup =
			((word  & FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F) != 0);

		rss->u.basicvirtual.hashtoeplitz =
			((word & FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ_F) != 0);

		/* we need at least Tunnel Map Enable to be set */
		if (!rss->u.basicvirtual.tnlmapen)
			return -EINVAL;
		break;
	}

	default:
		/* all unknown/unsupported RSS modes result in an error */
		return -EINVAL;
	}

	return 0;
}