#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm1105_dev {size_t boardnr; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_sda; } ;

/* Variables and functions */
 TYPE_1__* dm1105_boards ; 
 scalar_t__ dm1105_gpio_get (struct dm1105_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm1105_getsda(void *data)
{
	struct dm1105_dev *dev = data;

	return dm1105_gpio_get(dev, dm1105_boards[dev->boardnr].gpio_sda)
									? 1 : 0;
}