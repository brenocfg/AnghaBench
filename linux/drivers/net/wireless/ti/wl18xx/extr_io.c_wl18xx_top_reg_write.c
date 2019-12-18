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
typedef  int u16 ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int wlcore_read32 (struct wl1271*,int,int*) ; 
 int wlcore_write32 (struct wl1271*,int,int) ; 

int wl18xx_top_reg_write(struct wl1271 *wl, int addr, u16 val)
{
	u32 tmp;
	int ret;

	if (WARN_ON(addr % 2))
		return -EINVAL;

	if ((addr % 4) == 0) {
		ret = wlcore_read32(wl, addr, &tmp);
		if (ret < 0)
			goto out;

		tmp = (tmp & 0xffff0000) | val;
		ret = wlcore_write32(wl, addr, tmp);
	} else {
		ret = wlcore_read32(wl, addr - 2, &tmp);
		if (ret < 0)
			goto out;

		tmp = (tmp & 0xffff) | (val << 16);
		ret = wlcore_write32(wl, addr - 2, tmp);
	}

out:
	return ret;
}