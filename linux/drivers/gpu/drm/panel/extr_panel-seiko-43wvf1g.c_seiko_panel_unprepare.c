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
struct seiko_panel {int prepared; int /*<<< orphan*/  dvdd; int /*<<< orphan*/  avdd; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct seiko_panel* to_seiko_panel (struct drm_panel*) ; 

__attribute__((used)) static int seiko_panel_unprepare(struct drm_panel *panel)
{
	struct seiko_panel *p = to_seiko_panel(panel);

	if (!p->prepared)
		return 0;

	regulator_disable(p->avdd);

	/* Add a 100ms delay as per the panel datasheet */
	msleep(100);

	regulator_disable(p->dvdd);

	p->prepared = false;

	return 0;
}