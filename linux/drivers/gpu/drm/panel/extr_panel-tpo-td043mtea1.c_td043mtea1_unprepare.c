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
struct td043mtea1_panel {int /*<<< orphan*/  spi_suspended; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  td043mtea1_power_off (struct td043mtea1_panel*) ; 
 struct td043mtea1_panel* to_td043mtea1_device (struct drm_panel*) ; 

__attribute__((used)) static int td043mtea1_unprepare(struct drm_panel *panel)
{
	struct td043mtea1_panel *lcd = to_td043mtea1_device(panel);

	if (!lcd->spi_suspended)
		td043mtea1_power_off(lcd);

	return 0;
}