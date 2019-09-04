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
struct net_device {int dummy; } ;
struct ksz_port {TYPE_1__* linked; } ;
struct dev_priv {scalar_t__ media_state; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_connected ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_media_state (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_link(struct net_device *dev, struct dev_priv *priv,
	struct ksz_port *port)
{
	if (priv->media_state != port->linked->state) {
		priv->media_state = port->linked->state;
		if (netif_running(dev))
			set_media_state(dev, media_connected);
	}
}