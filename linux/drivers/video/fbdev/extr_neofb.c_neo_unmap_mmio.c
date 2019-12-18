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
struct neofb_par {int /*<<< orphan*/ * mmio_vbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; } ;
struct fb_info {TYPE_1__ fix; struct neofb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void neo_unmap_mmio(struct fb_info *info)
{
	struct neofb_par *par = info->par;

	DBG("neo_unmap_mmio");

	iounmap(par->mmio_vbase);
	par->mmio_vbase = NULL;

	release_mem_region(info->fix.mmio_start,
			   info->fix.mmio_len);
}