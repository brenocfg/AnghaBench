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
struct dwc2_hsotg {int frame_list_sz; scalar_t__ frame_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  frame_list_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int FRLISTEN_64_SIZE ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kzalloc (int,int) ; 

__attribute__((used)) static int dwc2_frame_list_alloc(struct dwc2_hsotg *hsotg, gfp_t mem_flags)
{
	if (hsotg->frame_list)
		return 0;

	hsotg->frame_list_sz = 4 * FRLISTEN_64_SIZE;
	hsotg->frame_list = kzalloc(hsotg->frame_list_sz, GFP_ATOMIC | GFP_DMA);
	if (!hsotg->frame_list)
		return -ENOMEM;

	hsotg->frame_list_dma = dma_map_single(hsotg->dev, hsotg->frame_list,
					       hsotg->frame_list_sz,
					       DMA_TO_DEVICE);

	return 0;
}