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
struct qede_vlan {scalar_t__ vid; int /*<<< orphan*/  list; scalar_t__ configured; } ;
struct qede_dev {int /*<<< orphan*/  non_configured_vlans; int /*<<< orphan*/  configured_vlans; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qede_vlan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_del_vlan_from_list(struct qede_dev *edev,
				    struct qede_vlan *vlan)
{
	/* vlan0 filter isn't consuming out of our quota */
	if (vlan->vid != 0) {
		if (vlan->configured)
			edev->configured_vlans--;
		else
			edev->non_configured_vlans--;
	}

	list_del(&vlan->list);
	kfree(vlan);
}