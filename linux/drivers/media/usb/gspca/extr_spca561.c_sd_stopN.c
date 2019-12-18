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

/* Variables and functions */
 scalar_t__ Rev012A ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->chip_revision == Rev012A) {
		reg_w_val(gspca_dev, 0x8112, 0x0e);
		/* Led Off (bit 3 -> 1 */
		reg_w_val(gspca_dev, 0x8114, 0x08);
	} else {
		reg_w_val(gspca_dev, 0x8112, 0x20);
/*		reg_w_val(gspca_dev, 0x8102, 0x00); ?? */
	}
}