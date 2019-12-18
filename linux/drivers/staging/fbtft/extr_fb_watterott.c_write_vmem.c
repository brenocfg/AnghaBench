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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {scalar_t__* buf; } ;
struct TYPE_7__ {int (* write ) (struct fbtft_par*,scalar_t__*,int) ;} ;
struct fbtft_par {TYPE_5__* info; TYPE_3__ txbuf; TYPE_2__ fbtftops; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_9__ {size_t line_length; } ;
struct TYPE_6__ {int xres; } ;
struct TYPE_10__ {TYPE_4__ fix; TYPE_1__ var; scalar_t__ screen_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LCD_DRAWIMAGE ; 
 int /*<<< orphan*/  COLOR_RGB565 ; 
 scalar_t__ cpu_to_be16 (int) ; 
 int stub1 (struct fbtft_par*,scalar_t__*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int write_vmem(struct fbtft_par *par, size_t offset, size_t len)
{
	unsigned int start_line, end_line;
	u16 *vmem16 = (u16 *)(par->info->screen_buffer + offset);
	__be16 *pos = par->txbuf.buf + 1;
	__be16 *buf16 = par->txbuf.buf + 10;
	int i, j;
	int ret = 0;

	start_line = offset / par->info->fix.line_length;
	end_line = start_line + (len / par->info->fix.line_length) - 1;

	/* Set command header. pos: x, y, w, h */
	((u8 *)par->txbuf.buf)[0] = CMD_LCD_DRAWIMAGE;
	pos[0] = 0;
	pos[2] = cpu_to_be16(par->info->var.xres);
	pos[3] = cpu_to_be16(1);
	((u8 *)par->txbuf.buf)[9] = COLOR_RGB565;

	for (i = start_line; i <= end_line; i++) {
		pos[1] = cpu_to_be16(i);
		for (j = 0; j < par->info->var.xres; j++)
			buf16[j] = cpu_to_be16(*vmem16++);
		ret = par->fbtftops.write(par,
			par->txbuf.buf, 10 + par->info->fix.line_length);
		if (ret < 0)
			return ret;
		udelay(300);
	}

	return 0;
}