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
struct sd {scalar_t__ chip_revision; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int __u16 ;

/* Variables and functions */
 scalar_t__ Rev012A ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u16 reg;

	if (sd->chip_revision == Rev012A)
		reg = 0x8610;
	else
		reg = 0x8611;

	reg_w_val(gspca_dev, reg + 0, val);		/* R */
	reg_w_val(gspca_dev, reg + 1, val);		/* Gr */
	reg_w_val(gspca_dev, reg + 2, val);		/* B */
	reg_w_val(gspca_dev, reg + 3, val);		/* Gb */
}