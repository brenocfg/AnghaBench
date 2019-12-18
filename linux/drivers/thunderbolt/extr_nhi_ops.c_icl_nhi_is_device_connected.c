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
struct tb_nhi {int /*<<< orphan*/  pdev; } ;
struct tb {TYPE_1__* root_switch; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_for_device ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tb* pci_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_nhi_is_device_connected(struct tb_nhi *nhi)
{
	struct tb *tb = pci_get_drvdata(nhi->pdev);
	int ret;

	ret = device_for_each_child(&tb->root_switch->dev, NULL,
				    check_for_device);
	return ret > 0;
}