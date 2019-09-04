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
struct sd {int reg08; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZC3XX_R008_CLOCKSETTING ; 
 int /*<<< orphan*/ * jpeg_qual ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setquality(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	jpeg_set_qual(sd->jpeg_hdr, jpeg_qual[sd->reg08 >> 1]);
	reg_w(gspca_dev, sd->reg08, ZC3XX_R008_CLOCKSETTING);
}