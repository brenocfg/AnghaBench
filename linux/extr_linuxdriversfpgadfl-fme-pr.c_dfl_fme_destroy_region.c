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
struct dfl_fme_region {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfl_fme_destroy_region(struct dfl_fme_region *fme_region)
{
	platform_device_unregister(fme_region->region);
}