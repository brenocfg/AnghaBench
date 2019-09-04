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
struct TYPE_2__ {int /*<<< orphan*/  vram_size; scalar_t__ vram_base; } ;
struct cirrus_device {TYPE_1__ mc; int /*<<< orphan*/ * rmmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cirrus_vram_fini(struct cirrus_device *cdev)
{
	iounmap(cdev->rmmio);
	cdev->rmmio = NULL;
	if (cdev->mc.vram_base)
		release_mem_region(cdev->mc.vram_base, cdev->mc.vram_size);
}