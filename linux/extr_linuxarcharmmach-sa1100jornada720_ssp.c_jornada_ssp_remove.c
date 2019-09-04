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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GPIO25 ; 
 int /*<<< orphan*/  GPSR ; 
 int /*<<< orphan*/  ssp_exit () ; 

__attribute__((used)) static int jornada_ssp_remove(struct platform_device *dev)
{
	/* Note that this doesn't actually remove the driver, since theres nothing to remove
	 * It just makes sure everything is turned off */
	GPSR = GPIO_GPIO25;
	ssp_exit();
	return 0;
}