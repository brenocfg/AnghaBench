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
struct ls037v7dw01_panel {int /*<<< orphan*/  vdd; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct ls037v7dw01_panel* to_ls037v7dw01_device (struct drm_panel*) ; 

__attribute__((used)) static int ls037v7dw01_unprepare(struct drm_panel *panel)
{
	struct ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);

	regulator_disable(lcd->vdd);
	return 0;
}