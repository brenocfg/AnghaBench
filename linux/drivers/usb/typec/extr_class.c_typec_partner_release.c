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
struct typec_partner {int /*<<< orphan*/  mode_ids; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct typec_partner*) ; 
 struct typec_partner* to_typec_partner (struct device*) ; 

__attribute__((used)) static void typec_partner_release(struct device *dev)
{
	struct typec_partner *partner = to_typec_partner(dev);

	ida_destroy(&partner->mode_ids);
	kfree(partner);
}