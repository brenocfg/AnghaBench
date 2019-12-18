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
struct adv7511 {int /*<<< orphan*/  dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_dsi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_device_unregister (int /*<<< orphan*/ ) ; 

void adv7533_detach_dsi(struct adv7511 *adv)
{
	mipi_dsi_detach(adv->dsi);
	mipi_dsi_device_unregister(adv->dsi);
}