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
typedef  int u8 ;
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 int DMA_BURST16 ; 
 int DMA_BURST32 ; 
 int of_getintprop_default (struct device_node*,char*,int) ; 

__attribute__((used)) static u8 qec_get_burst(struct device_node *dp)
{
	u8 bsizes, bsizes_more;

	/* Find and set the burst sizes for the QEC, since it
	 * does the actual dma for all 4 channels.
	 */
	bsizes = of_getintprop_default(dp, "burst-sizes", 0xff);
	bsizes &= 0xff;
	bsizes_more = of_getintprop_default(dp->parent, "burst-sizes", 0xff);

	if (bsizes_more != 0xff)
		bsizes &= bsizes_more;
	if (bsizes == 0xff || (bsizes & DMA_BURST16) == 0 ||
	    (bsizes & DMA_BURST32)==0)
		bsizes = (DMA_BURST32 - 1);

	return bsizes;
}