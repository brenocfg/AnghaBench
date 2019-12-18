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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD8 (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,unsigned int const) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_rf_init_calibration(struct rt2x00_dev *rt2x00dev,
				       const unsigned int rf_reg)
{
	u8 rfcsr;

	rfcsr = rt2800_rfcsr_read(rt2x00dev, rf_reg);
	rt2x00_set_field8(&rfcsr, FIELD8(0x80), 1);
	rt2800_rfcsr_write(rt2x00dev, rf_reg, rfcsr);
	msleep(1);
	rt2x00_set_field8(&rfcsr, FIELD8(0x80), 0);
	rt2800_rfcsr_write(rt2x00dev, rf_reg, rfcsr);
}