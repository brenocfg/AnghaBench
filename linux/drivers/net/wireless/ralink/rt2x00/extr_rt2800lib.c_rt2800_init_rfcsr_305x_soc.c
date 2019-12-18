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
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_305x_soc(struct rt2x00_dev *rt2x00dev)
{
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 0, 0x50);
	rt2800_rfcsr_write(rt2x00dev, 1, 0x01);
	rt2800_rfcsr_write(rt2x00dev, 2, 0xf7);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x75);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x50);
	rt2800_rfcsr_write(rt2x00dev, 8, 0x39);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x0f);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x60);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x75);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x75);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x58);
	rt2800_rfcsr_write(rt2x00dev, 16, 0xb3);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x92);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x2c);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 20, 0xba);
	rt2800_rfcsr_write(rt2x00dev, 21, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x31);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x01);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x25);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x23);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x13);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x83);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x00);
}