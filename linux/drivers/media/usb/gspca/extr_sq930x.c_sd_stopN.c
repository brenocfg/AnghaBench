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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ SENSOR_MT9V111 ; 
 int /*<<< orphan*/  SQ930_GPIO_DFL_LED ; 
 int /*<<< orphan*/  gpio_set (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_stop (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_MT9V111)
		gpio_set(sd, 0, SQ930_GPIO_DFL_LED);
	send_stop(gspca_dev);
}