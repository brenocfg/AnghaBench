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
struct TYPE_3__ {scalar_t__ af_list_max; scalar_t__ afcache_size; int /*<<< orphan*/  picode; } ;
struct TYPE_4__ {TYPE_1__ stat_info; } ;
struct fmdev {TYPE_2__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_NO_PI_CODE ; 

void fm_rx_reset_station_info(struct fmdev *fmdev)
{
	fmdev->rx.stat_info.picode = FM_NO_PI_CODE;
	fmdev->rx.stat_info.afcache_size = 0;
	fmdev->rx.stat_info.af_list_max = 0;
}