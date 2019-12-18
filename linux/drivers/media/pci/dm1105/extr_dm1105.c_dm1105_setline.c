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
typedef  int /*<<< orphan*/  u32 ;
struct dm1105_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm1105_gpio_clear (struct dm1105_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm1105_gpio_enable (struct dm1105_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm1105_setline(struct dm1105_dev *dev, u32 line, int state)
{
	if (state)
		dm1105_gpio_enable(dev, line, 0);
	else {
		dm1105_gpio_enable(dev, line, 1);
		dm1105_gpio_clear(dev, line);
	}
}