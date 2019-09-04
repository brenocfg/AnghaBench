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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int orient1; int orient2; int /*<<< orphan*/  (* get_xyz ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ vflag; } ;

/* Variables and functions */
 TYPE_1__ ams_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ams_sensors(s8 *x, s8 *y, s8 *z)
{
	u32 orient = ams_info.vflag? ams_info.orient1 : ams_info.orient2;

	if (orient & 0x80)
		/* X and Y swapped */
		ams_info.get_xyz(y, x, z);
	else
		ams_info.get_xyz(x, y, z);

	if (orient & 0x04)
		*z = ~(*z);
	if (orient & 0x02)
		*y = ~(*y);
	if (orient & 0x01)
		*x = ~(*x);
}