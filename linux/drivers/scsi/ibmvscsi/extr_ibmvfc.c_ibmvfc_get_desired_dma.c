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
typedef  union ibmvfc_iu {int dummy; } ibmvfc_iu ;
struct vio_dev {int dummy; } ;
struct TYPE_2__ {int cmd_per_lun; } ;

/* Variables and functions */
 TYPE_1__ driver_template ; 
 int max_requests ; 

__attribute__((used)) static unsigned long ibmvfc_get_desired_dma(struct vio_dev *vdev)
{
	unsigned long pool_dma = max_requests * sizeof(union ibmvfc_iu);
	return pool_dma + ((512 * 1024) * driver_template.cmd_per_lun);
}