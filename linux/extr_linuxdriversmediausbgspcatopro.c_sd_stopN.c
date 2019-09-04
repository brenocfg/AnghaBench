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

/* Variables and functions */
 scalar_t__ BRIDGE_TP6800 ; 
 int /*<<< orphan*/  TP6800_R21_ENDP_1_CTL ; 
 int /*<<< orphan*/  TP6800_R2F_TIMING_CFG ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->bridge == BRIDGE_TP6800)
		reg_w(gspca_dev, TP6800_R2F_TIMING_CFG, 0x03);
	set_led(gspca_dev, 0);
	reg_w(gspca_dev, TP6800_R21_ENDP_1_CTL, 0x00);
}