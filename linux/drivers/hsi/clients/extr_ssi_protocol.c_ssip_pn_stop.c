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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsi_release_port (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_unregister_port_event (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_reset (struct hsi_client*) ; 
 struct hsi_client* to_hsi_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssip_pn_stop(struct net_device *dev)
{
	struct hsi_client *cl = to_hsi_client(dev->dev.parent);

	ssip_reset(cl);
	hsi_unregister_port_event(cl);
	hsi_release_port(cl);

	return 0;
}