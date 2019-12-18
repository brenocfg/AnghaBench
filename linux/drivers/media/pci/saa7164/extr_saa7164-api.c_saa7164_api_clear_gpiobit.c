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
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int saa7164_api_modify_gpio (struct saa7164_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int saa7164_api_clear_gpiobit(struct saa7164_dev *dev, u8 unitid,
	u8 pin)
{
	return saa7164_api_modify_gpio(dev, unitid, pin, 0);
}