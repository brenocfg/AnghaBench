#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ioctl_len; scalar_t__ mem_addr; int /*<<< orphan*/ * mem_ptr; int /*<<< orphan*/ * ioremap_ptr; int /*<<< orphan*/  max_cmds; scalar_t__ ioctl_datasize; TYPE_5__* ioctl_data; int /*<<< orphan*/  ioctl_busaddr; TYPE_1__* pcidev; int /*<<< orphan*/ * subsys; int /*<<< orphan*/ * nvram; TYPE_5__* logical_drive_info; int /*<<< orphan*/  logical_drive_info_dma_addr; TYPE_5__* adapt; int /*<<< orphan*/ * conf; TYPE_5__* enq; int /*<<< orphan*/  enq_busaddr; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_8__ {int /*<<< orphan*/  hw_status_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  IPS_LD_INFO ;
typedef  int /*<<< orphan*/  IPS_IO_CMD ;
typedef  int /*<<< orphan*/  IPS_ENQ ;
typedef  int /*<<< orphan*/  IPS_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ips_deallocatescbs (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ips_free(ips_ha_t * ha)
{

	METHOD_TRACE("ips_free", 1);

	if (ha) {
		if (ha->enq) {
			dma_free_coherent(&ha->pcidev->dev, sizeof(IPS_ENQ),
					    ha->enq, ha->enq_busaddr);
			ha->enq = NULL;
		}

		kfree(ha->conf);
		ha->conf = NULL;

		if (ha->adapt) {
			dma_free_coherent(&ha->pcidev->dev,
					    sizeof (IPS_ADAPTER) +
					    sizeof (IPS_IO_CMD), ha->adapt,
					    ha->adapt->hw_status_start);
			ha->adapt = NULL;
		}

		if (ha->logical_drive_info) {
			dma_free_coherent(&ha->pcidev->dev,
					    sizeof (IPS_LD_INFO),
					    ha->logical_drive_info,
					    ha->logical_drive_info_dma_addr);
			ha->logical_drive_info = NULL;
		}

		kfree(ha->nvram);
		ha->nvram = NULL;

		kfree(ha->subsys);
		ha->subsys = NULL;

		if (ha->ioctl_data) {
			dma_free_coherent(&ha->pcidev->dev, ha->ioctl_len,
					    ha->ioctl_data, ha->ioctl_busaddr);
			ha->ioctl_data = NULL;
			ha->ioctl_datasize = 0;
			ha->ioctl_len = 0;
		}
		ips_deallocatescbs(ha, ha->max_cmds);

		/* free memory mapped (if applicable) */
		if (ha->mem_ptr) {
			iounmap(ha->ioremap_ptr);
			ha->ioremap_ptr = NULL;
			ha->mem_ptr = NULL;
		}

		ha->mem_addr = 0;

	}
}