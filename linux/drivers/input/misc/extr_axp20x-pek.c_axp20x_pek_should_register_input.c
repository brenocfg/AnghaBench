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
struct platform_device {int dummy; } ;
struct axp20x_pek {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool axp20x_pek_should_register_input(struct axp20x_pek *axp20x_pek,
					     struct platform_device *pdev)
{
	return true;
}