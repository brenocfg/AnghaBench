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
struct efa_dev {int /*<<< orphan*/  addr; TYPE_1__* pdev; int /*<<< orphan*/  mtu; } ;
struct efa_com_get_network_attr_result {int /*<<< orphan*/  mtu; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void efa_update_network_attr(struct efa_dev *dev,
				    struct efa_com_get_network_attr_result *network_attr)
{
	memcpy(dev->addr, network_attr->addr, sizeof(network_attr->addr));
	dev->mtu = network_attr->mtu;

	dev_dbg(&dev->pdev->dev, "Full address %pI6\n", dev->addr);
}