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
struct sd {TYPE_1__* sensor; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int (* init_controls ) (struct sd*) ;} ;

/* Variables and functions */
 int stub1 (struct sd*) ; 

__attribute__((used)) static int m5602_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!sd->sensor->init_controls)
		return 0;

	return sd->sensor->init_controls(sd);
}