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
typedef  int u32 ;
struct fw_caps_config_cmd {void* op_to_write; void* cfvalid_to_len16; } ;
struct TYPE_5__ {int tx_modq_map; } ;
struct TYPE_6__ {TYPE_2__ tp; } ;
struct TYPE_4__ {int /*<<< orphan*/  egr_sz; } ;
struct adapter {int /*<<< orphan*/  pf; TYPE_3__ params; TYPE_1__ sge; int /*<<< orphan*/  mbox; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int CSUM_HAS_PSEUDO_HDR_F ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_CMD ; 
 int /*<<< orphan*/  FW_CMD_CAP_PF ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int FW_LEN16 (struct fw_caps_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL ; 
 int FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F ; 
 int FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F ; 
 int HPZ0_V (scalar_t__) ; 
 int /*<<< orphan*/  MAX_INGQ ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  T4_TX_MODQ_10G_WEIGHT_DEFAULT ; 
 int TP_INGRESS_CONFIG_A ; 
 int /*<<< orphan*/  TP_PIO_ADDR_A ; 
 int /*<<< orphan*/  TP_PIO_DATA_A ; 
 int /*<<< orphan*/  TP_SHIFT_CNT_A ; 
 int /*<<< orphan*/  TP_TX_MOD_CHANNEL_WEIGHT_A ; 
 int /*<<< orphan*/  TP_TX_MOD_QUEUE_REQ_MAP_A ; 
 int /*<<< orphan*/  TP_TX_MOD_QUEUE_WEIGHT0_A ; 
 int /*<<< orphan*/  TP_TX_SCHED_FIFO_A ; 
 int /*<<< orphan*/  TP_TX_SCHED_HDR_A ; 
 int /*<<< orphan*/  TP_TX_SCHED_PCMD_A ; 
 int TX_MODQ_WEIGHT0_V (int /*<<< orphan*/ ) ; 
 int TX_MODQ_WEIGHT1_V (int /*<<< orphan*/ ) ; 
 int TX_MODQ_WEIGHT2_V (int /*<<< orphan*/ ) ; 
 int TX_MODQ_WEIGHT3_V (int /*<<< orphan*/ ) ; 
 int TX_MOD_QUEUE_REQ_MAP_V (int) ; 
 int /*<<< orphan*/  ULP_RX_TDDP_PSZ_A ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* htonl (int) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int /*<<< orphan*/  memset (struct fw_caps_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_cfg_pfvf (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t4_config_glbl_rss (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int t4_early_init (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_get_pfres (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_sge_init (struct adapter*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_caps_config_cmd*,int,struct fw_caps_config_cmd*) ; 
 int /*<<< orphan*/  t4_write_indirect (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adap_init1(struct adapter *adap, struct fw_caps_config_cmd *c)
{
	u32 v;
	int ret;

	/* Now that we've successfully configured and initialized the adapter
	 * can ask the Firmware what resources it has provisioned for us.
	 */
	ret = t4_get_pfres(adap);
	if (ret) {
		dev_err(adap->pdev_dev,
			"Unable to retrieve resource provisioning information\n");
		return ret;
	}

	/* get device capabilities */
	memset(c, 0, sizeof(*c));
	c->op_to_write = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_READ_F);
	c->cfvalid_to_len16 = htonl(FW_LEN16(*c));
	ret = t4_wr_mbox(adap, adap->mbox, c, sizeof(*c), c);
	if (ret < 0)
		return ret;

	c->op_to_write = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	ret = t4_wr_mbox(adap, adap->mbox, c, sizeof(*c), NULL);
	if (ret < 0)
		return ret;

	ret = t4_config_glbl_rss(adap, adap->pf,
				 FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL,
				 FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F |
				 FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F);
	if (ret < 0)
		return ret;

	ret = t4_cfg_pfvf(adap, adap->mbox, adap->pf, 0, adap->sge.egr_sz, 64,
			  MAX_INGQ, 0, 0, 4, 0xf, 0xf, 16, FW_CMD_CAP_PF,
			  FW_CMD_CAP_PF);
	if (ret < 0)
		return ret;

	t4_sge_init(adap);

	/* tweak some settings */
	t4_write_reg(adap, TP_SHIFT_CNT_A, 0x64f8849);
	t4_write_reg(adap, ULP_RX_TDDP_PSZ_A, HPZ0_V(PAGE_SHIFT - 12));
	t4_write_reg(adap, TP_PIO_ADDR_A, TP_INGRESS_CONFIG_A);
	v = t4_read_reg(adap, TP_PIO_DATA_A);
	t4_write_reg(adap, TP_PIO_DATA_A, v & ~CSUM_HAS_PSEUDO_HDR_F);

	/* first 4 Tx modulation queues point to consecutive Tx channels */
	adap->params.tp.tx_modq_map = 0xE4;
	t4_write_reg(adap, TP_TX_MOD_QUEUE_REQ_MAP_A,
		     TX_MOD_QUEUE_REQ_MAP_V(adap->params.tp.tx_modq_map));

	/* associate each Tx modulation queue with consecutive Tx channels */
	v = 0x84218421;
	t4_write_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_HDR_A);
	t4_write_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_FIFO_A);
	t4_write_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_PCMD_A);

#define T4_TX_MODQ_10G_WEIGHT_DEFAULT 16 /* in KB units */
	if (is_offload(adap)) {
		t4_write_reg(adap, TP_TX_MOD_QUEUE_WEIGHT0_A,
			     TX_MODQ_WEIGHT0_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT1_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT2_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT3_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT));
		t4_write_reg(adap, TP_TX_MOD_CHANNEL_WEIGHT_A,
			     TX_MODQ_WEIGHT0_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT1_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT2_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT3_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT));
	}

	/* get basic stuff going */
	return t4_early_init(adap, adap->pf);
}