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
struct b53_device {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_configure_vlan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_set_forwarding (struct b53_device*,int) ; 

__attribute__((used)) static int b53_apply_config(struct b53_device *priv)
{
	/* disable switching */
	b53_set_forwarding(priv, 0);

	b53_configure_vlan(priv->ds);

	/* enable switching */
	b53_set_forwarding(priv, 1);

	return 0;
}