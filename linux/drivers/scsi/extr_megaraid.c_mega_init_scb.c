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
struct TYPE_6__ {int idx; int /*<<< orphan*/  list; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  state; int /*<<< orphan*/  dma_type; int /*<<< orphan*/ * epthru; int /*<<< orphan*/  epthru_dma_addr; int /*<<< orphan*/ * pthru; int /*<<< orphan*/  pthru_dma_addr; int /*<<< orphan*/ * sgl; int /*<<< orphan*/ * sgl64; int /*<<< orphan*/  sgl_dma_addr; } ;
typedef  TYPE_1__ scb_t ;
typedef  int /*<<< orphan*/  mega_sglist ;
typedef  int /*<<< orphan*/  mega_sgl64 ;
typedef  int /*<<< orphan*/  mega_passthru ;
typedef  int /*<<< orphan*/  mega_ext_passthru ;
struct TYPE_7__ {int max_cmds; int sglen; int /*<<< orphan*/  free_list; TYPE_3__* dev; TYPE_1__* scb_list; } ;
typedef  TYPE_2__ adapter_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGA_DMA_TYPE_NONE ; 
 int /*<<< orphan*/  SCB_FREE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mega_free_sgl (TYPE_2__*) ; 
 void* pci_alloc_consistent (TYPE_3__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mega_init_scb(adapter_t *adapter)
{
	scb_t	*scb;
	int	i;

	for( i = 0; i < adapter->max_cmds; i++ ) {

		scb = &adapter->scb_list[i];

		scb->sgl64 = NULL;
		scb->sgl = NULL;
		scb->pthru = NULL;
		scb->epthru = NULL;
	}

	for( i = 0; i < adapter->max_cmds; i++ ) {

		scb = &adapter->scb_list[i];

		scb->idx = i;

		scb->sgl64 = pci_alloc_consistent(adapter->dev,
				sizeof(mega_sgl64) * adapter->sglen,
				&scb->sgl_dma_addr);

		scb->sgl = (mega_sglist *)scb->sgl64;

		if( !scb->sgl ) {
			dev_warn(&adapter->dev->dev, "RAID: Can't allocate sglist\n");
			mega_free_sgl(adapter);
			return -1;
		}

		scb->pthru = pci_alloc_consistent(adapter->dev,
				sizeof(mega_passthru),
				&scb->pthru_dma_addr);

		if( !scb->pthru ) {
			dev_warn(&adapter->dev->dev, "RAID: Can't allocate passthru\n");
			mega_free_sgl(adapter);
			return -1;
		}

		scb->epthru = pci_alloc_consistent(adapter->dev,
				sizeof(mega_ext_passthru),
				&scb->epthru_dma_addr);

		if( !scb->epthru ) {
			dev_warn(&adapter->dev->dev,
				"Can't allocate extended passthru\n");
			mega_free_sgl(adapter);
			return -1;
		}


		scb->dma_type = MEGA_DMA_TYPE_NONE;

		/*
		 * Link to free list
		 * lock not required since we are loading the driver, so no
		 * commands possible right now.
		 */
		scb->state = SCB_FREE;
		scb->cmd = NULL;
		list_add(&scb->list, &adapter->free_list);
	}

	return 0;
}