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
typedef  int u32 ;
struct titsc {unsigned int coordinate_readouts; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FIFO0 ; 
 int /*<<< orphan*/  sort (unsigned int*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  titsc_cmp_coord ; 
 void* titsc_readl (struct titsc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void titsc_read_coordinates(struct titsc *ts_dev,
		u32 *x, u32 *y, u32 *z1, u32 *z2)
{
	unsigned int yvals[7], xvals[7];
	unsigned int i, xsum = 0, ysum = 0;
	unsigned int creads = ts_dev->coordinate_readouts;

	for (i = 0; i < creads; i++) {
		yvals[i] = titsc_readl(ts_dev, REG_FIFO0);
		yvals[i] &= 0xfff;
	}

	*z1 = titsc_readl(ts_dev, REG_FIFO0);
	*z1 &= 0xfff;
	*z2 = titsc_readl(ts_dev, REG_FIFO0);
	*z2 &= 0xfff;

	for (i = 0; i < creads; i++) {
		xvals[i] = titsc_readl(ts_dev, REG_FIFO0);
		xvals[i] &= 0xfff;
	}

	/*
	 * If co-ordinates readouts is less than 4 then
	 * report the average. In case of 4 or more
	 * readouts, sort the co-ordinate samples, drop
	 * min and max values and report the average of
	 * remaining values.
	 */
	if (creads <=  3) {
		for (i = 0; i < creads; i++) {
			ysum += yvals[i];
			xsum += xvals[i];
		}
		ysum /= creads;
		xsum /= creads;
	} else {
		sort(yvals, creads, sizeof(unsigned int),
		     titsc_cmp_coord, NULL);
		sort(xvals, creads, sizeof(unsigned int),
		     titsc_cmp_coord, NULL);
		for (i = 1; i < creads - 1; i++) {
			ysum += yvals[i];
			xsum += xvals[i];
		}
		ysum /= creads - 2;
		xsum /= creads - 2;
	}
	*y = ysum;
	*x = xsum;
}