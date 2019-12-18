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
struct aspeed_video_addr {unsigned int size; int /*<<< orphan*/  virt; int /*<<< orphan*/  dma; } ;
struct aspeed_video {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool aspeed_video_alloc_buf(struct aspeed_video *video,
				   struct aspeed_video_addr *addr,
				   unsigned int size)
{
	addr->virt = dma_alloc_coherent(video->dev, size, &addr->dma,
					GFP_KERNEL);
	if (!addr->virt)
		return false;

	addr->size = size;
	return true;
}