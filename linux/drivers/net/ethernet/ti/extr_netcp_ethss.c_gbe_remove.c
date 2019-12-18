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
struct netcp_device {int dummy; } ;
struct gbe_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  gbe_intf_head; int /*<<< orphan*/  tx_pipe; int /*<<< orphan*/  ale; int /*<<< orphan*/  cpts; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_ale_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpts_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_secondary_ports (struct gbe_priv*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netcp_txpipe_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gbe_remove(struct netcp_device *netcp_device, void *inst_priv)
{
	struct gbe_priv *gbe_dev = inst_priv;

	del_timer_sync(&gbe_dev->timer);
	cpts_release(gbe_dev->cpts);
	cpsw_ale_stop(gbe_dev->ale);
	netcp_txpipe_close(&gbe_dev->tx_pipe);
	free_secondary_ports(gbe_dev);

	if (!list_empty(&gbe_dev->gbe_intf_head))
		dev_alert(gbe_dev->dev,
			  "unreleased ethss interfaces present\n");

	return 0;
}