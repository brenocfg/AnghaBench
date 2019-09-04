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
struct coh_dma_channel {int dummy; } ;
struct coh901318_chan {size_t id; } ;

/* Variables and functions */
 struct coh_dma_channel const* chan_config ; 

__attribute__((used)) static inline const struct coh_dma_channel *
cohc_chan_conf(struct coh901318_chan *cohc)
{
	return &chan_config[cohc->id];
}