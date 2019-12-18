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
typedef  size_t u32 ;
struct mb862xxfb_par {int dummy; } ;
struct fb_info {struct mb862xxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDC_GEO_REG_INPUT_FIFO ; 
 int /*<<< orphan*/  GDC_REG_FIFO_COUNT ; 
 int /*<<< orphan*/  draw ; 
 int /*<<< orphan*/  geo ; 
 scalar_t__ inreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void mb862xxfb_write_fifo(u32 count, u32 *data, struct fb_info *info)
{
	struct mb862xxfb_par *par = info->par;
	static u32 free;

	u32 total = 0;
	while (total < count) {
		if (free) {
			outreg(geo, GDC_GEO_REG_INPUT_FIFO, data[total]);
			total++;
			free--;
		} else {
			free = (u32) inreg(draw, GDC_REG_FIFO_COUNT);
		}
	}
}