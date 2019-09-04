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
struct mdc_chan {int chan_nr; int /*<<< orphan*/  mdma; } ;

/* Variables and functions */
 scalar_t__ mdc_readl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 mdc_chan_readl(struct mdc_chan *mchan, u32 reg)
{
	return mdc_readl(mchan->mdma, mchan->chan_nr * 0x040 + reg);
}