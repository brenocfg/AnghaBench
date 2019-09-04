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
struct sd {int reg08; } ;
struct TYPE_2__ {int needs_full_bandwidth; } ;
struct gspca_dev {TYPE_1__ cam; } ;

/* Variables and functions */

__attribute__((used)) static int sd_pre_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	gspca_dev->cam.needs_full_bandwidth = (sd->reg08 >= 4) ? 1 : 0;
	return 0;
}