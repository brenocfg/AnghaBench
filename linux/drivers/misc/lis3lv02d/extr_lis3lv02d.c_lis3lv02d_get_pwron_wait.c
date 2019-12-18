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
struct lis3lv02d {int pwron_delay; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int lis3lv02d_get_odr (struct lis3lv02d*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lis3lv02d_get_pwron_wait(struct lis3lv02d *lis3)
{
	int div = lis3lv02d_get_odr(lis3);

	if (WARN_ONCE(div == 0, "device returned spurious data"))
		return -ENXIO;

	/* LIS3 power on delay is quite long */
	msleep(lis3->pwron_delay / div);
	return 0;
}