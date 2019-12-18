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
struct aspeed_video_addr {unsigned long long dma; int /*<<< orphan*/ * virt; scalar_t__ size; } ;
struct aspeed_video {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,unsigned long long) ; 

__attribute__((used)) static void aspeed_video_free_buf(struct aspeed_video *video,
				  struct aspeed_video_addr *addr)
{
	dma_free_coherent(video->dev, addr->size, addr->virt, addr->dma);
	addr->size = 0;
	addr->dma = 0ULL;
	addr->virt = NULL;
}