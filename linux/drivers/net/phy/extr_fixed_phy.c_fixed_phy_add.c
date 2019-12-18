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
struct fixed_phy_status {int dummy; } ;

/* Variables and functions */
 int fixed_phy_add_gpiod (unsigned int,int,struct fixed_phy_status*,int /*<<< orphan*/ *) ; 

int fixed_phy_add(unsigned int irq, int phy_addr,
		  struct fixed_phy_status *status) {

	return fixed_phy_add_gpiod(irq, phy_addr, status, NULL);
}