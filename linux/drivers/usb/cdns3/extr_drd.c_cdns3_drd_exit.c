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
struct cdns3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_otg_disable_irq (struct cdns3*) ; 

int cdns3_drd_exit(struct cdns3 *cdns)
{
	cdns3_otg_disable_irq(cdns);
	return 0;
}