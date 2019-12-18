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
struct lbs_private {scalar_t__ mesh_dev; scalar_t__ dev; } ;

/* Variables and functions */
 int netif_running (scalar_t__) ; 

__attribute__((used)) static inline int lbs_iface_active(struct lbs_private *priv)
{
	int r;

	r = netif_running(priv->dev);
	if (priv->mesh_dev)
		r |= netif_running(priv->mesh_dev);

	return r;
}