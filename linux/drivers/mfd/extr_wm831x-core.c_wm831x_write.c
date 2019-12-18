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
typedef  int /*<<< orphan*/  u16 ;
struct wm831x {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EPERM ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 scalar_t__ wm831x_reg_locked (struct wm831x*,unsigned short) ; 

__attribute__((used)) static int wm831x_write(struct wm831x *wm831x, unsigned short reg,
			int bytes, void *src)
{
	u16 *buf = src;
	int i, ret;

	BUG_ON(bytes % 2);
	BUG_ON(bytes <= 0);

	for (i = 0; i < bytes / 2; i++) {
		if (wm831x_reg_locked(wm831x, reg))
			return -EPERM;

		dev_vdbg(wm831x->dev, "Write %04x to R%d(0x%x)\n",
			 buf[i], reg + i, reg + i);
		ret = regmap_write(wm831x->regmap, reg + i, buf[i]);
		if (ret != 0)
			return ret;
	}

	return 0;
}