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
struct omap_dma_channel_params {scalar_t__ write_prio; scalar_t__ read_prio; int /*<<< orphan*/  dst_fi; int /*<<< orphan*/  dst_ei; int /*<<< orphan*/  dst_start; int /*<<< orphan*/  dst_amode; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_fi; int /*<<< orphan*/  src_ei; int /*<<< orphan*/  src_start; int /*<<< orphan*/  src_amode; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_or_dst_synch; int /*<<< orphan*/  trigger; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  frame_count; int /*<<< orphan*/  elem_count; int /*<<< orphan*/  data_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dma_set_prio_lch (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  omap_set_dma_dest_params (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_src_params (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_transfer_params (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap_set_dma_params(int lch, struct omap_dma_channel_params *params)
{
	omap_set_dma_transfer_params(lch, params->data_type,
				     params->elem_count, params->frame_count,
				     params->sync_mode, params->trigger,
				     params->src_or_dst_synch);
	omap_set_dma_src_params(lch, params->src_port,
				params->src_amode, params->src_start,
				params->src_ei, params->src_fi);

	omap_set_dma_dest_params(lch, params->dst_port,
				 params->dst_amode, params->dst_start,
				 params->dst_ei, params->dst_fi);
	if (params->read_prio || params->write_prio)
		omap_dma_set_prio_lch(lch, params->read_prio,
				      params->write_prio);
}