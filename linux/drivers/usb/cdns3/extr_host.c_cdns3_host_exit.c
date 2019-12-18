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
struct cdns3 {int /*<<< orphan*/ * host_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_drd_switch_host (struct cdns3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_host_exit(struct cdns3 *cdns)
{
	platform_device_unregister(cdns->host_dev);
	cdns->host_dev = NULL;
	cdns3_drd_switch_host(cdns, 0);
}