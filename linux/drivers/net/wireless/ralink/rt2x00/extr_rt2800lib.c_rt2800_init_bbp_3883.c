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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_init_bbp_early (struct rt2x00_dev*) ; 

__attribute__((used)) static void rt2800_init_bbp_3883(struct rt2x00_dev *rt2x00dev)
{
	rt2800_init_bbp_early(rt2x00dev);

	rt2800_bbp_write(rt2x00dev, 4, 0x50);
	rt2800_bbp_write(rt2x00dev, 47, 0x48);

	rt2800_bbp_write(rt2x00dev, 86, 0x46);
	rt2800_bbp_write(rt2x00dev, 88, 0x90);

	rt2800_bbp_write(rt2x00dev, 92, 0x02);

	rt2800_bbp_write(rt2x00dev, 103, 0xc0);
	rt2800_bbp_write(rt2x00dev, 104, 0x92);
	rt2800_bbp_write(rt2x00dev, 105, 0x34);
	rt2800_bbp_write(rt2x00dev, 106, 0x12);
	rt2800_bbp_write(rt2x00dev, 120, 0x50);
	rt2800_bbp_write(rt2x00dev, 137, 0x0f);
	rt2800_bbp_write(rt2x00dev, 163, 0x9d);

	/* Set ITxBF timeout to 0x9C40=1000msec */
	rt2800_bbp_write(rt2x00dev, 179, 0x02);
	rt2800_bbp_write(rt2x00dev, 180, 0x00);
	rt2800_bbp_write(rt2x00dev, 182, 0x40);
	rt2800_bbp_write(rt2x00dev, 180, 0x01);
	rt2800_bbp_write(rt2x00dev, 182, 0x9c);

	rt2800_bbp_write(rt2x00dev, 179, 0x00);

	/* Reprogram the inband interface to put right values in RXWI */
	rt2800_bbp_write(rt2x00dev, 142, 0x04);
	rt2800_bbp_write(rt2x00dev, 143, 0x3b);
	rt2800_bbp_write(rt2x00dev, 142, 0x06);
	rt2800_bbp_write(rt2x00dev, 143, 0xa0);
	rt2800_bbp_write(rt2x00dev, 142, 0x07);
	rt2800_bbp_write(rt2x00dev, 143, 0xa1);
	rt2800_bbp_write(rt2x00dev, 142, 0x08);
	rt2800_bbp_write(rt2x00dev, 143, 0xa2);
	rt2800_bbp_write(rt2x00dev, 148, 0xc8);
}