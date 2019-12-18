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
struct s3c2410fb_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_start; int /*<<< orphan*/  smem_len; } ;
struct fb_info {int /*<<< orphan*/  screen_base; TYPE_1__ fix; struct s3c2410fb_info* par; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,struct s3c2410fb_info*,unsigned int,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int s3c2410fb_map_video_memory(struct fb_info *info)
{
	struct s3c2410fb_info *fbi = info->par;
	dma_addr_t map_dma;
	unsigned map_size = PAGE_ALIGN(info->fix.smem_len);

	dprintk("map_video_memory(fbi=%p) map_size %u\n", fbi, map_size);

	info->screen_base = dma_alloc_wc(fbi->dev, map_size, &map_dma,
					 GFP_KERNEL);

	if (info->screen_base) {
		/* prevent initial garbage on screen */
		dprintk("map_video_memory: clear %p:%08x\n",
			info->screen_base, map_size);
		memset(info->screen_base, 0x00, map_size);

		info->fix.smem_start = map_dma;

		dprintk("map_video_memory: dma=%08lx cpu=%p size=%08x\n",
			info->fix.smem_start, info->screen_base, map_size);
	}

	return info->screen_base ? 0 : -ENOMEM;
}