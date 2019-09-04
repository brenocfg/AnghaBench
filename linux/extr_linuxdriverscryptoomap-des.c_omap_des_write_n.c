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
struct omap_des_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_des_write (struct omap_des_dev*,int,int) ; 

__attribute__((used)) static void omap_des_write_n(struct omap_des_dev *dd, u32 offset,
					u32 *value, int count)
{
	for (; count--; value++, offset += 4)
		omap_des_write(dd, offset, *value);
}