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
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  region; } ;
struct fmdev {TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * region_configs ; 

void fmc_update_region_info(struct fmdev *fmdev, u8 region_to_set)
{
	fmdev->rx.region = region_configs[region_to_set];
}