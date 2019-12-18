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
typedef  scalar_t__ ulong ;
struct scsi_qla_host {scalar_t__ nx_pcibase; } ;
struct crb_128M_2M_sub_block_map {scalar_t__ start_128M; scalar_t__ end_128M; scalar_t__ start_2M; scalar_t__ valid; } ;
struct TYPE_2__ {struct crb_128M_2M_sub_block_map* sub_block; } ;

/* Variables and functions */
 size_t CRB_BLK (scalar_t__) ; 
 size_t CRB_SUBBLK (scalar_t__) ; 
 scalar_t__ QLA82XX_CRB_MAX ; 
 scalar_t__ QLA82XX_PCI_CAMQM ; 
 scalar_t__ QLA82XX_PCI_CAMQM_2M_BASE ; 
 scalar_t__ QLA82XX_PCI_CAMQM_2M_END ; 
 scalar_t__ QLA82XX_PCI_CRBSPACE ; 
 TYPE_1__* crb_128M_2M_map ; 

int
qla4_82xx_pci_get_crb_addr_2M(struct scsi_qla_host *ha, ulong *off)
{
	struct crb_128M_2M_sub_block_map *m;

	if (*off >= QLA82XX_CRB_MAX)
		return -1;

	if (*off >= QLA82XX_PCI_CAMQM && (*off < QLA82XX_PCI_CAMQM_2M_END)) {
		*off = (*off - QLA82XX_PCI_CAMQM) +
		    QLA82XX_PCI_CAMQM_2M_BASE + ha->nx_pcibase;
		return 0;
	}

	if (*off < QLA82XX_PCI_CRBSPACE)
		return -1;

	*off -= QLA82XX_PCI_CRBSPACE;
	/*
	 * Try direct map
	 */

	m = &crb_128M_2M_map[CRB_BLK(*off)].sub_block[CRB_SUBBLK(*off)];

	if (m->valid && (m->start_128M <= *off) && (m->end_128M > *off)) {
		*off = *off + m->start_2M - m->start_128M + ha->nx_pcibase;
		return 0;
	}

	/*
	 * Not in direct map, use crb window
	 */
	return 1;
}