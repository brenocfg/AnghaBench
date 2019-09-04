#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int psize; int /*<<< orphan*/  data_width; } ;
struct TYPE_3__ {int psize; int /*<<< orphan*/  data_width; } ;
struct stedma40_chan_cfg {scalar_t__ dir; TYPE_2__ src_info; TYPE_1__ dst_info; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D40_MEM_LCSP1_SCFG_EIM_POS ; 
 int D40_MEM_LCSP1_SCFG_ESIZE_POS ; 
 int /*<<< orphan*/  D40_MEM_LCSP1_SCFG_INCR_POS ; 
 int /*<<< orphan*/  D40_MEM_LCSP1_SCFG_MST_POS ; 
 int D40_MEM_LCSP1_SCFG_PSIZE_POS ; 
 int /*<<< orphan*/  D40_MEM_LCSP3_DCFG_EIM_POS ; 
 int D40_MEM_LCSP3_DCFG_ESIZE_POS ; 
 int /*<<< orphan*/  D40_MEM_LCSP3_DCFG_INCR_POS ; 
 int /*<<< orphan*/  D40_MEM_LCSP3_DCFG_MST_POS ; 
 int D40_MEM_LCSP3_DCFG_PSIZE_POS ; 
 scalar_t__ DMA_DEV_TO_DEV ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ DMA_MEM_TO_MEM ; 
 int d40_width_to_bits (int /*<<< orphan*/ ) ; 

void d40_log_cfg(struct stedma40_chan_cfg *cfg,
		 u32 *lcsp1, u32 *lcsp3)
{
	u32 l3 = 0; /* dst */
	u32 l1 = 0; /* src */

	/* src is mem? -> increase address pos */
	if (cfg->dir ==  DMA_MEM_TO_DEV ||
	    cfg->dir ==  DMA_MEM_TO_MEM)
		l1 |= BIT(D40_MEM_LCSP1_SCFG_INCR_POS);

	/* dst is mem? -> increase address pos */
	if (cfg->dir ==  DMA_DEV_TO_MEM ||
	    cfg->dir ==  DMA_MEM_TO_MEM)
		l3 |= BIT(D40_MEM_LCSP3_DCFG_INCR_POS);

	/* src is hw? -> master port 1 */
	if (cfg->dir ==  DMA_DEV_TO_MEM ||
	    cfg->dir ==  DMA_DEV_TO_DEV)
		l1 |= BIT(D40_MEM_LCSP1_SCFG_MST_POS);

	/* dst is hw? -> master port 1 */
	if (cfg->dir ==  DMA_MEM_TO_DEV ||
	    cfg->dir ==  DMA_DEV_TO_DEV)
		l3 |= BIT(D40_MEM_LCSP3_DCFG_MST_POS);

	l3 |= BIT(D40_MEM_LCSP3_DCFG_EIM_POS);
	l3 |= cfg->dst_info.psize << D40_MEM_LCSP3_DCFG_PSIZE_POS;
	l3 |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_MEM_LCSP3_DCFG_ESIZE_POS;

	l1 |= BIT(D40_MEM_LCSP1_SCFG_EIM_POS);
	l1 |= cfg->src_info.psize << D40_MEM_LCSP1_SCFG_PSIZE_POS;
	l1 |= d40_width_to_bits(cfg->src_info.data_width)
		<< D40_MEM_LCSP1_SCFG_ESIZE_POS;

	*lcsp1 = l1;
	*lcsp3 = l3;

}