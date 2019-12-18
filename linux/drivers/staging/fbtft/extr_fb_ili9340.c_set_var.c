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
struct fbtft_par {int bgr; TYPE_2__* info; } ;
struct TYPE_3__ {int rotate; } ;
struct TYPE_4__ {TYPE_1__ var; } ;

/* Variables and functions */
 int ILI9340_MADCTL_MV ; 
 int ILI9340_MADCTL_MX ; 
 int ILI9340_MADCTL_MY ; 
 int /*<<< orphan*/  MIPI_DCS_SET_ADDRESS_MODE ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_var(struct fbtft_par *par)
{
	u8 val;

	switch (par->info->var.rotate) {
	case 270:
		val = ILI9340_MADCTL_MV;
		break;
	case 180:
		val = ILI9340_MADCTL_MY;
		break;
	case 90:
		val = ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX;
		break;
	default:
		val = ILI9340_MADCTL_MX;
		break;
	}
	/* Memory Access Control  */
	write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, val | (par->bgr << 3));

	return 0;
}