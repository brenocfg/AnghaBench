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
struct serdes_am654 {int busy; int /*<<< orphan*/  control; int /*<<< orphan*/  type; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_NONE ; 
 int /*<<< orphan*/  mux_control_deselect (int /*<<< orphan*/ ) ; 
 struct serdes_am654* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static void serdes_am654_release(struct phy *x)
{
	struct serdes_am654 *phy = phy_get_drvdata(x);

	phy->type = PHY_NONE;
	phy->busy = false;
	mux_control_deselect(phy->control);
}