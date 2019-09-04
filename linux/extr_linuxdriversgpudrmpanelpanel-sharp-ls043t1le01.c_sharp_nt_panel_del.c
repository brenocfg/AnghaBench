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
struct TYPE_2__ {scalar_t__ dev; } ;
struct sharp_nt_panel {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (TYPE_1__*) ; 

__attribute__((used)) static void sharp_nt_panel_del(struct sharp_nt_panel *sharp_nt)
{
	if (sharp_nt->base.dev)
		drm_panel_remove(&sharp_nt->base);
}