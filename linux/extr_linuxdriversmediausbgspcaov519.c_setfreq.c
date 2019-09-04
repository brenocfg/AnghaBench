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
struct sd {scalar_t__ bridge; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ BRIDGE_W9968CF ; 
 int /*<<< orphan*/  setfreq_i (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w9968cf_set_crop_window (struct sd*) ; 

__attribute__((used)) static void setfreq(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	setfreq_i(sd, val);

	/* Ugly but necessary */
	if (sd->bridge == BRIDGE_W9968CF)
		w9968cf_set_crop_window(sd);
}