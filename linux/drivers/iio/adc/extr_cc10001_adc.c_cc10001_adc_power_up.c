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
struct cc10001_adc_device {int /*<<< orphan*/  start_delay_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC10001_ADC_POWER_DOWN ; 
 int /*<<< orphan*/  cc10001_adc_write_reg (struct cc10001_adc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc10001_adc_power_up(struct cc10001_adc_device *adc_dev)
{
	cc10001_adc_write_reg(adc_dev, CC10001_ADC_POWER_DOWN, 0);
	ndelay(adc_dev->start_delay_ns);
}