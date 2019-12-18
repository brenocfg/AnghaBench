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
struct rapl_if_priv {TYPE_1__* platform_rapl_domain; int /*<<< orphan*/  control_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  power_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  powercap_unregister_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rapl_remove_platform_domain(struct rapl_if_priv *priv)
{
	if (priv->platform_rapl_domain) {
		powercap_unregister_zone(priv->control_type,
				 &priv->platform_rapl_domain->power_zone);
		kfree(priv->platform_rapl_domain);
	}
}