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
struct TYPE_2__ {scalar_t__ streaming; } ;
struct sd {TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV519_R51_RESET1 ; 
 int OV7670_MVFP_MIRROR ; 
 int OV7670_MVFP_VFLIP ; 
 int /*<<< orphan*/  OV7670_R1E_MVFP ; 
 int /*<<< orphan*/  i2c_w_mask (struct sd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sethvflip(struct gspca_dev *gspca_dev, s32 hflip, s32 vflip)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->gspca_dev.streaming)
		reg_w(sd, OV519_R51_RESET1, 0x0f);	/* block stream */
	i2c_w_mask(sd, OV7670_R1E_MVFP,
		OV7670_MVFP_MIRROR * hflip | OV7670_MVFP_VFLIP * vflip,
		OV7670_MVFP_MIRROR | OV7670_MVFP_VFLIP);
	if (sd->gspca_dev.streaming)
		reg_w(sd, OV519_R51_RESET1, 0x00);	/* restart stream */
}