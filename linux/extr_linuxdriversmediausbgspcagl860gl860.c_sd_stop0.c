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
struct TYPE_2__ {int /*<<< orphan*/  present; } ;
struct sd {void (* dev_post_unset_alt ) (struct gspca_dev*) ;TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 void stub1 (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!sd->gspca_dev.present)
		return;

	return sd->dev_post_unset_alt(gspca_dev);
}