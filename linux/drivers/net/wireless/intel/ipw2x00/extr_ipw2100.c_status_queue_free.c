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
struct TYPE_2__ {int /*<<< orphan*/ * drv; int /*<<< orphan*/  nic; int /*<<< orphan*/  size; } ;
struct ipw2100_priv {TYPE_1__ status_queue; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void status_queue_free(struct ipw2100_priv *priv)
{
	IPW_DEBUG_INFO("enter\n");

	if (priv->status_queue.drv) {
		pci_free_consistent(priv->pci_dev, priv->status_queue.size,
				    priv->status_queue.drv,
				    priv->status_queue.nic);
		priv->status_queue.drv = NULL;
	}

	IPW_DEBUG_INFO("exit\n");
}