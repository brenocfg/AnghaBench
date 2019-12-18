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
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_X ; 
 int /*<<< orphan*/  AMS_Y ; 
 int /*<<< orphan*/  AMS_Z ; 
 int /*<<< orphan*/  ams_pmu_get_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ams_pmu_get_xyz(s8 *x, s8 *y, s8 *z)
{
	*x = ams_pmu_get_register(AMS_X);
	*y = ams_pmu_get_register(AMS_Y);
	*z = ams_pmu_get_register(AMS_Z);
}