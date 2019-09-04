#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ipu_channel_param {int dummy; } ipu_channel_param ;
typedef  int uint32_t ;
struct ipu {long channel_init_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int chan_id; } ;
struct idmac_channel {int /*<<< orphan*/  desc; TYPE_1__ dma_chan; union ipu_channel_param params; } ;
struct idmac {int dummy; } ;
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
 int EINVAL ; 
 int FS_ENC_IN_VALID ; 
 int /*<<< orphan*/  IC_CONF ; 
 int IC_CONF_CSI_MEM_WR_EN ; 
#define  IDMAC_IC_0 131 
#define  IDMAC_IC_7 130 
#define  IDMAC_SDC_0 129 
#define  IDMAC_SDC_1 128 
 int /*<<< orphan*/  IPU_CONF ; 
 int /*<<< orphan*/  IPU_FS_PROC_FLOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dump_idmac_reg (struct ipu*) ; 
 int idmac_desc_alloc (struct idmac_channel*,int) ; 
 int idmac_read_icreg (struct ipu*,int /*<<< orphan*/ ) ; 
 int idmac_read_ipureg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_icreg (struct ipu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_ipureg (struct ipu*,int,int /*<<< orphan*/ ) ; 
 int ipu_channel_conf_mask (int) ; 
 int ipu_ic_init_prpenc (struct ipu*,union ipu_channel_param*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipu* to_ipu (struct idmac*) ; 

__attribute__((used)) static int ipu_init_channel(struct idmac *idmac, struct idmac_channel *ichan)
{
	union ipu_channel_param *params = &ichan->params;
	uint32_t ipu_conf;
	enum ipu_channel channel = ichan->dma_chan.chan_id;
	unsigned long flags;
	uint32_t reg;
	struct ipu *ipu = to_ipu(idmac);
	int ret = 0, n_desc = 0;

	dev_dbg(ipu->dev, "init channel = %d\n", channel);

	if (channel != IDMAC_SDC_0 && channel != IDMAC_SDC_1 &&
	    channel != IDMAC_IC_7)
		return -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	switch (channel) {
	case IDMAC_IC_7:
		n_desc = 16;
		reg = idmac_read_icreg(ipu, IC_CONF);
		idmac_write_icreg(ipu, reg & ~IC_CONF_CSI_MEM_WR_EN, IC_CONF);
		break;
	case IDMAC_IC_0:
		n_desc = 16;
		reg = idmac_read_ipureg(ipu, IPU_FS_PROC_FLOW);
		idmac_write_ipureg(ipu, reg & ~FS_ENC_IN_VALID, IPU_FS_PROC_FLOW);
		ret = ipu_ic_init_prpenc(ipu, params, true);
		break;
	case IDMAC_SDC_0:
	case IDMAC_SDC_1:
		n_desc = 4;
	default:
		break;
	}

	ipu->channel_init_mask |= 1L << channel;

	/* Enable IPU sub module */
	ipu_conf = idmac_read_ipureg(ipu, IPU_CONF) |
		ipu_channel_conf_mask(channel);
	idmac_write_ipureg(ipu, ipu_conf, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);

	if (n_desc && !ichan->desc)
		ret = idmac_desc_alloc(ichan, n_desc);

	dump_idmac_reg(ipu);

	return ret;
}