#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_13__ {int* buf; } ;
struct TYPE_12__ {int (* write ) (struct fbtft_par*,int*,size_t) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  dc; } ;
struct fbtft_par {TYPE_8__* info; TYPE_7__* pdata; TYPE_5__ txbuf; TYPE_4__ fbtftops; TYPE_2__ gpio; } ;
struct TYPE_11__ {int /*<<< orphan*/  rotate; } ;
struct TYPE_9__ {int line_length; } ;
struct TYPE_16__ {int /*<<< orphan*/  device; TYPE_3__ var; TYPE_1__ fix; scalar_t__ screen_buffer; } ;
struct TYPE_14__ {int buswidth; } ;
struct TYPE_15__ {TYPE_6__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct fbtft_par*,int*,size_t) ; 
 int stub2 (struct fbtft_par*,int*,size_t) ; 

__attribute__((used)) static int write_vmem(struct fbtft_par *par, size_t offset, size_t len)
{
	u8 *vmem8 = (u8 *)(par->info->screen_buffer);
	u8 *buf8 = par->txbuf.buf;
	u16 *buf16 = par->txbuf.buf;
	int line_length = par->info->fix.line_length;
	int y_start = offset / line_length;
	int y_end = (offset + len - 1) / line_length;
	int x, y, i;
	int ret = 0;

	switch (par->pdata->display.buswidth) {
	case 8:
		switch (par->info->var.rotate) {
		case 90:
		case 270:
			i = y_start * line_length;
			for (y = y_start; y <= y_end; y++) {
				for (x = 0; x < line_length; x += 2) {
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + 1] & 0xF0;
					buf8++;
					i += 2;
				}
			}
			break;
		default:
			/* Must be even because pages are two lines */
			y_start &= 0xFE;
			i = y_start * line_length;
			for (y = y_start; y <= y_end; y += 2) {
				for (x = 0; x < line_length; x++) {
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + line_length] & 0xF0;
					buf8++;
					i++;
				}
				i += line_length;
			}
			break;
		}
		gpiod_set_value(par->gpio.dc, 1);

		/* Write data */
		ret = par->fbtftops.write(par, par->txbuf.buf, len / 2);
		break;
	case 9:
		switch (par->info->var.rotate) {
		case 90:
		case 270:
			i = y_start * line_length;
			for (y = y_start; y <= y_end; y++) {
				for (x = 0; x < line_length; x += 2) {
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + 1] & 0xF0;
					buf16++;
					i += 2;
				}
			}
			break;
		default:
			/* Must be even because pages are two lines */
			y_start &= 0xFE;
			i = y_start * line_length;
			for (y = y_start; y <= y_end; y += 2) {
				for (x = 0; x < line_length; x++) {
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + line_length] & 0xF0;
					buf16++;
					i++;
				}
				i += line_length;
			}
			break;
		}

		/* Write data */
		ret = par->fbtftops.write(par, par->txbuf.buf, len);
		break;
	default:
		dev_err(par->info->device, "unsupported buswidth %d\n",
			par->pdata->display.buswidth);
	}

	if (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);

	return ret;
}