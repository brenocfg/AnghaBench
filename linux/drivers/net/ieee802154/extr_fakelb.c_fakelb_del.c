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
struct fakelb_phy {int /*<<< orphan*/  hw; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fakelb_del(struct fakelb_phy *phy)
{
	list_del(&phy->list);

	ieee802154_unregister_hw(phy->hw);
	ieee802154_free_hw(phy->hw);
}