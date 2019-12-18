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
struct xen_pcibk_device {int dummy; } ;
typedef  int /*<<< orphan*/  publish_pci_root_cb ;
struct TYPE_2__ {int (* publish ) (struct xen_pcibk_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct xen_pcibk_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* xen_pcibk_backend ; 

__attribute__((used)) static inline int xen_pcibk_publish_pci_roots(struct xen_pcibk_device *pdev,
					      publish_pci_root_cb cb)
{
	if (xen_pcibk_backend && xen_pcibk_backend->publish)
		return xen_pcibk_backend->publish(pdev, cb);
	return -1;
}