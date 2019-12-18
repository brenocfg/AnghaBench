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
struct pcf2123_data {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL2_AIE ; 
 int /*<<< orphan*/  PCF2123_REG_CTRL2 ; 
 struct pcf2123_data* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf2123_rtc_alarm_irq_enable(struct device *dev, unsigned int en)
{
	struct pcf2123_data *pcf2123 = dev_get_drvdata(dev);

	return regmap_update_bits(pcf2123->map, PCF2123_REG_CTRL2, CTRL2_AIE,
				  en ? CTRL2_AIE : 0);
}