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
struct spi_device {int dummy; } ;
struct lis3lv02d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lis3_dev ; 
 int /*<<< orphan*/  lis3lv02d_joystick_disable (struct lis3lv02d*) ; 
 int /*<<< orphan*/  lis3lv02d_poweroff (struct lis3lv02d*) ; 
 int lis3lv02d_remove_fs (int /*<<< orphan*/ *) ; 
 struct lis3lv02d* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int lis302dl_spi_remove(struct spi_device *spi)
{
	struct lis3lv02d *lis3 = spi_get_drvdata(spi);
	lis3lv02d_joystick_disable(lis3);
	lis3lv02d_poweroff(lis3);

	return lis3lv02d_remove_fs(&lis3_dev);
}