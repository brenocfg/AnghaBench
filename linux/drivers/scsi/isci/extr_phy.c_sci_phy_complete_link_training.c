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
typedef  int /*<<< orphan*/  u32 ;
struct isci_phy {int max_negotiated_speed; int /*<<< orphan*/  sm; } ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;

/* Variables and functions */
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_phy_complete_link_training(struct isci_phy *iphy,
					   enum sas_linkrate max_link_rate,
					   u32 next_state)
{
	iphy->max_negotiated_speed = max_link_rate;

	sci_change_state(&iphy->sm, next_state);
}