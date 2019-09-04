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
struct platform_device {int dummy; } ;
struct dev_archdata {int numa_node; struct platform_device* op; void* host_controller; void* stc; void* iommu; } ;

/* Variables and functions */

__attribute__((used)) static void pci_init_dev_archdata(struct dev_archdata *sd, void *iommu,
				  void *stc, void *host_controller,
				  struct platform_device  *op,
				  int numa_node)
{
	sd->iommu = iommu;
	sd->stc = stc;
	sd->host_controller = host_controller;
	sd->op = op;
	sd->numa_node = numa_node;
}