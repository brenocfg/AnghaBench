#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time64_t ;
struct TYPE_3__ {int lcv_time; scalar_t__ lcv; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int ktime_get_seconds () ; 

__attribute__((used)) static int hilse_init_lcv(hil_mlc *mlc, int unused)
{
	time64_t now = ktime_get_seconds();

	if (mlc->lcv && (now - mlc->lcv_time) < 5)
		return -1;

	mlc->lcv_time = now;
	mlc->lcv = 0;

	return 0;
}