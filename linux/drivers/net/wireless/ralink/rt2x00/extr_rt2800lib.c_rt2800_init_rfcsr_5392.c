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
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_5xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_5392(struct rt2x00_dev *rt2x00dev)
{
	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_write(rt2x00dev, 1, 0x17);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x88);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 6, 0xe0);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x46);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x4d);
	rt2800_rfcsr_write(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 21, 0x8d);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x0b);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x44);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x09);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 33, 0xC0);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 37, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x89);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x1b);
	rt2800_rfcsr_write(rt2x00dev, 40, 0x0f);
	rt2800_rfcsr_write(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_write(rt2x00dev, 42, 0xd5);
	rt2800_rfcsr_write(rt2x00dev, 43, 0x9b);
	rt2800_rfcsr_write(rt2x00dev, 44, 0x0e);
	rt2800_rfcsr_write(rt2x00dev, 45, 0xa2);
	rt2800_rfcsr_write(rt2x00dev, 46, 0x73);
	rt2800_rfcsr_write(rt2x00dev, 47, 0x0c);
	rt2800_rfcsr_write(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 49, 0x94);
	rt2800_rfcsr_write(rt2x00dev, 50, 0x94);
	rt2800_rfcsr_write(rt2x00dev, 51, 0x3a);
	rt2800_rfcsr_write(rt2x00dev, 52, 0x48);
	rt2800_rfcsr_write(rt2x00dev, 53, 0x44);
	rt2800_rfcsr_write(rt2x00dev, 54, 0x38);
	rt2800_rfcsr_write(rt2x00dev, 55, 0x43);
	rt2800_rfcsr_write(rt2x00dev, 56, 0xa1);
	rt2800_rfcsr_write(rt2x00dev, 57, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 58, 0x39);
	rt2800_rfcsr_write(rt2x00dev, 59, 0x07);
	rt2800_rfcsr_write(rt2x00dev, 60, 0x45);
	rt2800_rfcsr_write(rt2x00dev, 61, 0x91);
	rt2800_rfcsr_write(rt2x00dev, 62, 0x39);
	rt2800_rfcsr_write(rt2x00dev, 63, 0x07);

	rt2800_normal_mode_setup_5xxx(rt2x00dev);

	rt2800_led_open_drain_enable(rt2x00dev);
}