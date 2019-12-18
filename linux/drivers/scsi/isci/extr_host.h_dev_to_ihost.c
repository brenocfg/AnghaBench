#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isci_host {int dummy; } ;
struct domain_device {TYPE_2__* port; } ;
struct TYPE_4__ {TYPE_1__* ha; } ;
struct TYPE_3__ {struct isci_host* lldd_ha; } ;

/* Variables and functions */

__attribute__((used)) static inline struct isci_host *dev_to_ihost(struct domain_device *dev)
{
	return dev->port->ha->lldd_ha;
}