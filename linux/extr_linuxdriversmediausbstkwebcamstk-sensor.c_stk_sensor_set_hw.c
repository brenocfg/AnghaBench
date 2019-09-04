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
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HREF ; 
 int /*<<< orphan*/  REG_HSTART ; 
 int /*<<< orphan*/  REG_HSTOP ; 
 int /*<<< orphan*/  REG_VREF ; 
 int /*<<< orphan*/  REG_VSTART ; 
 int /*<<< orphan*/  REG_VSTOP ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stk_sensor_inb (struct stk_camera*,int /*<<< orphan*/ ,unsigned char*) ; 
 int stk_sensor_outb (struct stk_camera*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int stk_sensor_set_hw(struct stk_camera *dev,
		int hstart, int hstop, int vstart, int vstop)
{
	int ret;
	unsigned char v;
/*
 * Horizontal: 11 bits, top 8 live in hstart and hstop.  Bottom 3 of
 * hstart are in href[2:0], bottom 3 of hstop in href[5:3].  There is
 * a mystery "edge offset" value in the top two bits of href.
 */
	ret =  stk_sensor_outb(dev, REG_HSTART, (hstart >> 3) & 0xff);
	ret += stk_sensor_outb(dev, REG_HSTOP, (hstop >> 3) & 0xff);
	ret += stk_sensor_inb(dev, REG_HREF, &v);
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstart & 0x7);
	msleep(10);
	ret += stk_sensor_outb(dev, REG_HREF, v);
/*
 * Vertical: similar arrangement (note: this is different from ov7670.c)
 */
	ret += stk_sensor_outb(dev, REG_VSTART, (vstart >> 3) & 0xff);
	ret += stk_sensor_outb(dev, REG_VSTOP, (vstop >> 3) & 0xff);
	ret += stk_sensor_inb(dev, REG_VREF, &v);
	v = (v & 0xc0) | ((vstop & 0x7) << 3) | (vstart & 0x7);
	msleep(10);
	ret += stk_sensor_outb(dev, REG_VREF, v);
	return ret;
}