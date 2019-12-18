#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  fm_band; } ;
struct TYPE_4__ {TYPE_1__ region; } ;
struct fmdev {TYPE_2__ rx; } ;

/* Variables and functions */

void fm_rx_get_region(struct fmdev *fmdev, u8 *region)
{
	*region = fmdev->rx.region.fm_band;
}