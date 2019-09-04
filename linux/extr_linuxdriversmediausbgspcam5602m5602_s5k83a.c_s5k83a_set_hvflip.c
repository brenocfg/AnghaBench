#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sd {TYPE_2__* vflip; TYPE_1__* hflip; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 int s5k83a_get_rotation (struct sd*,scalar_t__*) ; 
 int s5k83a_set_flip_real (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int s5k83a_set_hvflip(struct gspca_dev *gspca_dev)
{
	int err;
	u8 reg;
	struct sd *sd = (struct sd *) gspca_dev;
	int hflip = sd->hflip->val;
	int vflip = sd->vflip->val;

	err = s5k83a_get_rotation(sd, &reg);
	if (err < 0)
		return err;
	if (reg) {
		hflip = !hflip;
		vflip = !vflip;
	}

	err = s5k83a_set_flip_real(gspca_dev, vflip, hflip);
	return err;
}