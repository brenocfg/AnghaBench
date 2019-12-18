#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {TYPE_2__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  pci_info ;
struct TYPE_7__ {TYPE_1__* isp_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* pci_info_str ) (TYPE_3__*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int) ; 

__attribute__((used)) static ssize_t
qla2x00_pci_info_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	char pci_info[30];

	return scnprintf(buf, PAGE_SIZE, "%s\n",
			 vha->hw->isp_ops->pci_info_str(vha, pci_info,
							sizeof(pci_info)));
}