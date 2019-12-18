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
typedef  int u8 ;
struct fbtft_par {scalar_t__ bgr; TYPE_2__* info; } ;
struct TYPE_3__ {int rotate; } ;
struct TYPE_4__ {TYPE_1__ var; } ;

/* Variables and functions */
 int HX8357D_MADCTL_BGR ; 
 int HX8357D_MADCTL_MV ; 
 int HX8357D_MADCTL_MX ; 
 int HX8357D_MADCTL_MY ; 
 int HX8357D_MADCTL_RGB ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_var(struct fbtft_par *par)
{
	u8 val;

	switch (par->info->var.rotate) {
	case 270:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MX;
		break;
	case 180:
		val = 0;
		break;
	case 90:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MY;
		break;
	default:
		val = HX8357D_MADCTL_MX | HX8357D_MADCTL_MY;
		break;
	}

	val |= (par->bgr ? HX8357D_MADCTL_RGB : HX8357D_MADCTL_BGR);

	/* Memory Access Control */
	write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, val);

	return 0;
}