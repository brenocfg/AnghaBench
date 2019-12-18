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
struct nvidia_par {int /*<<< orphan*/  PGRAPH; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
 scalar_t__ NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvidiafb_safe_mode (struct fb_info*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline void NVSync(struct fb_info *info)
{
	struct nvidia_par *par = info->par;
	int count = 1000000000;

	while (--count && NV_RD32(par->PGRAPH, 0x0700)) ;

	if (!count) {
		printk("nvidiafb: DMA Sync lockup\n");
		nvidiafb_safe_mode(info);
	}
}