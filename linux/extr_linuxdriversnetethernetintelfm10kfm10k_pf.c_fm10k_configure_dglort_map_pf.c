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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct fm10k_hw {int dummy; } ;
struct fm10k_dglort_cfg {int idx; int rss_l; int pc_l; int vsi_l; int vsi_b; int queue_l; int queue_b; scalar_t__ glort; scalar_t__ shared_l; scalar_t__ inner_rss; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  FM10K_DGLORTDEC (int) ; 
 scalar_t__ FM10K_DGLORTDEC_INNERRSS_ENABLE ; 
 scalar_t__ FM10K_DGLORTDEC_PCLENGTH_SHIFT ; 
 scalar_t__ FM10K_DGLORTDEC_QBASE_SHIFT ; 
 scalar_t__ FM10K_DGLORTDEC_RSSLENGTH_SHIFT ; 
 scalar_t__ FM10K_DGLORTDEC_VSIBASE_SHIFT ; 
 scalar_t__ FM10K_DGLORTDEC_VSILENGTH_SHIFT ; 
 int /*<<< orphan*/  FM10K_DGLORTMAP (int) ; 
 scalar_t__ FM10K_DGLORTMAP_ANY ; 
 scalar_t__ FM10K_DGLORTMAP_ZERO ; 
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 scalar_t__ FM10K_MAX_QUEUES ; 
 int /*<<< orphan*/  FM10K_RX_SGLORT (scalar_t__) ; 
 int /*<<< orphan*/  FM10K_TXQCTL (scalar_t__) ; 
 scalar_t__ FM10K_TXQCTL_PC_MASK ; 
 scalar_t__ FM10K_TXQCTL_PC_SHIFT ; 
 int /*<<< orphan*/  FM10K_TX_SGLORT (scalar_t__) ; 
 int fm10k_dglort_default ; 
 scalar_t__ fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32 fm10k_configure_dglort_map_pf(struct fm10k_hw *hw,
					 struct fm10k_dglort_cfg *dglort)
{
	u16 glort, queue_count, vsi_count, pc_count;
	u16 vsi, queue, pc, q_idx;
	u32 txqctl, dglortdec, dglortmap;

	/* verify the dglort pointer */
	if (!dglort)
		return FM10K_ERR_PARAM;

	/* verify the dglort values */
	if ((dglort->idx > 7) || (dglort->rss_l > 7) || (dglort->pc_l > 3) ||
	    (dglort->vsi_l > 6) || (dglort->vsi_b > 64) ||
	    (dglort->queue_l > 8) || (dglort->queue_b >= 256))
		return FM10K_ERR_PARAM;

	/* determine count of VSIs and queues */
	queue_count = BIT(dglort->rss_l + dglort->pc_l);
	vsi_count = BIT(dglort->vsi_l + dglort->queue_l);
	glort = dglort->glort;
	q_idx = dglort->queue_b;

	/* configure SGLORT for queues */
	for (vsi = 0; vsi < vsi_count; vsi++, glort++) {
		for (queue = 0; queue < queue_count; queue++, q_idx++) {
			if (q_idx >= FM10K_MAX_QUEUES)
				break;

			fm10k_write_reg(hw, FM10K_TX_SGLORT(q_idx), glort);
			fm10k_write_reg(hw, FM10K_RX_SGLORT(q_idx), glort);
		}
	}

	/* determine count of PCs and queues */
	queue_count = BIT(dglort->queue_l + dglort->rss_l + dglort->vsi_l);
	pc_count = BIT(dglort->pc_l);

	/* configure PC for Tx queues */
	for (pc = 0; pc < pc_count; pc++) {
		q_idx = pc + dglort->queue_b;
		for (queue = 0; queue < queue_count; queue++) {
			if (q_idx >= FM10K_MAX_QUEUES)
				break;

			txqctl = fm10k_read_reg(hw, FM10K_TXQCTL(q_idx));
			txqctl &= ~FM10K_TXQCTL_PC_MASK;
			txqctl |= pc << FM10K_TXQCTL_PC_SHIFT;
			fm10k_write_reg(hw, FM10K_TXQCTL(q_idx), txqctl);

			q_idx += pc_count;
		}
	}

	/* configure DGLORTDEC */
	dglortdec = ((u32)(dglort->rss_l) << FM10K_DGLORTDEC_RSSLENGTH_SHIFT) |
		    ((u32)(dglort->queue_b) << FM10K_DGLORTDEC_QBASE_SHIFT) |
		    ((u32)(dglort->pc_l) << FM10K_DGLORTDEC_PCLENGTH_SHIFT) |
		    ((u32)(dglort->vsi_b) << FM10K_DGLORTDEC_VSIBASE_SHIFT) |
		    ((u32)(dglort->vsi_l) << FM10K_DGLORTDEC_VSILENGTH_SHIFT) |
		    ((u32)(dglort->queue_l));
	if (dglort->inner_rss)
		dglortdec |=  FM10K_DGLORTDEC_INNERRSS_ENABLE;

	/* configure DGLORTMAP */
	dglortmap = (dglort->idx == fm10k_dglort_default) ?
			FM10K_DGLORTMAP_ANY : FM10K_DGLORTMAP_ZERO;
	dglortmap <<= dglort->vsi_l + dglort->queue_l + dglort->shared_l;
	dglortmap |= dglort->glort;

	/* write values to hardware */
	fm10k_write_reg(hw, FM10K_DGLORTDEC(dglort->idx), dglortdec);
	fm10k_write_reg(hw, FM10K_DGLORTMAP(dglort->idx), dglortmap);

	return 0;
}