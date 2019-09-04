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
struct cirrus_device {int /*<<< orphan*/  rmmio_size; int /*<<< orphan*/  rmmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_vram_fini (struct cirrus_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cirrus_device_fini(struct cirrus_device *cdev)
{
	release_mem_region(cdev->rmmio_base, cdev->rmmio_size);
	cirrus_vram_fini(cdev);
}