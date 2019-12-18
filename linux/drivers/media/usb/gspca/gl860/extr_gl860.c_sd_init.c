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
struct sd {int (* dev_init_at_startup ) (struct gspca_dev*) ;} ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int stub1 (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	return sd->dev_init_at_startup(gspca_dev);
}