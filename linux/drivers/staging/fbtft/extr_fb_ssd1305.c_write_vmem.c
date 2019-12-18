#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int* buf; } ;
struct TYPE_7__ {int (* write ) (struct fbtft_par*,int*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dc; } ;
struct fbtft_par {TYPE_5__* info; TYPE_3__ txbuf; TYPE_2__ fbtftops; TYPE_1__ gpio; } ;
struct TYPE_9__ {int xres; int yres; } ;
struct TYPE_10__ {int /*<<< orphan*/  device; TYPE_4__ var; scalar_t__ screen_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct fbtft_par*,int*,int) ; 

__attribute__((used)) static int write_vmem(struct fbtft_par *par, size_t offset, size_t len)
{
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf = par->txbuf.buf;
	int x, y, i;
	int ret;

	for (x = 0; x < par->info->var.xres; x++) {
		for (y = 0; y < par->info->var.yres / 8; y++) {
			*buf = 0x00;
			for (i = 0; i < 8; i++)
				*buf |= (vmem16[(y * 8 + i) *
						par->info->var.xres + x] ?
					 1 : 0) << i;
			buf++;
		}
	}

	/* Write data */
	gpiod_set_value(par->gpio.dc, 1);
	ret = par->fbtftops.write(par, par->txbuf.buf,
				  par->info->var.xres * par->info->var.yres /
				  8);
	if (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);
	return ret;
}