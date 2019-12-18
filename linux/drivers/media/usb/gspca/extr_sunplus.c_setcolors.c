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
typedef  int u16 ;
struct sd {scalar_t__ bridge; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ BRIDGE_SPCA536 ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setcolors(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 reg;

	reg = sd->bridge == BRIDGE_SPCA536 ? 0x20f6 : 0x21ae;
	reg_w_riv(gspca_dev, 0x00, reg, val);
}