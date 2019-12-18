#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ bdeSize; scalar_t__ bdeFlags; } ;
struct TYPE_6__ {void* w; TYPE_2__ f; } ;
struct ulp_bde64 {TYPE_3__ tus; void* addrHigh; void* addrLow; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpfc_hba {struct pci_dev* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; scalar_t__ virt; int /*<<< orphan*/  list; } ;
struct lpfc_dmabufext {int size; int flag; TYPE_1__ dma; } ;

/* Variables and functions */
 scalar_t__ BUFF_TYPE_BDE_64I ; 
 int BUF_SZ_4K ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diag_cmd_data_free (struct lpfc_hba*,struct lpfc_dmabufext*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct lpfc_dmabufext* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* putPaddrHigh (int /*<<< orphan*/ ) ; 
 void* putPaddrLow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lpfc_dmabufext *
diag_cmd_data_alloc(struct lpfc_hba *phba,
		   struct ulp_bde64 *bpl, uint32_t size,
		   int nocopydata)
{
	struct lpfc_dmabufext *mlist = NULL;
	struct lpfc_dmabufext *dmp;
	int cnt, offset = 0, i = 0;
	struct pci_dev *pcidev;

	pcidev = phba->pcidev;

	while (size) {
		/* We get chunks of 4K */
		if (size > BUF_SZ_4K)
			cnt = BUF_SZ_4K;
		else
			cnt = size;

		/* allocate struct lpfc_dmabufext buffer header */
		dmp = kmalloc(sizeof(struct lpfc_dmabufext), GFP_KERNEL);
		if (!dmp)
			goto out;

		INIT_LIST_HEAD(&dmp->dma.list);

		/* Queue it to a linked list */
		if (mlist)
			list_add_tail(&dmp->dma.list, &mlist->dma.list);
		else
			mlist = dmp;

		/* allocate buffer */
		dmp->dma.virt = dma_alloc_coherent(&pcidev->dev,
						   cnt,
						   &(dmp->dma.phys),
						   GFP_KERNEL);

		if (!dmp->dma.virt)
			goto out;

		dmp->size = cnt;

		if (nocopydata) {
			bpl->tus.f.bdeFlags = 0;
		} else {
			memset((uint8_t *)dmp->dma.virt, 0, cnt);
			bpl->tus.f.bdeFlags = BUFF_TYPE_BDE_64I;
		}

		/* build buffer ptr list for IOCB */
		bpl->addrLow = le32_to_cpu(putPaddrLow(dmp->dma.phys));
		bpl->addrHigh = le32_to_cpu(putPaddrHigh(dmp->dma.phys));
		bpl->tus.f.bdeSize = (ushort) cnt;
		bpl->tus.w = le32_to_cpu(bpl->tus.w);
		bpl++;

		i++;
		offset += cnt;
		size -= cnt;
	}

	if (mlist) {
		mlist->flag = i;
		return mlist;
	}
out:
	diag_cmd_data_free(phba, mlist);
	return NULL;
}