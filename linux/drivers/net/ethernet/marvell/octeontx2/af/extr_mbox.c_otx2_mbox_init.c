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
struct pci_dev {int dummy; } ;
struct otx2_mbox_dev {int /*<<< orphan*/  mbox_lock; void* mbase; } ;
struct otx2_mbox {int tr_shift; int ndevs; void* hwbase; struct otx2_mbox_dev* dev; struct pci_dev* pdev; void* reg_base; int /*<<< orphan*/  trigger; void* rx_size; void* tx_size; void* rx_start; void* tx_start; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MBOX_DIR_AFPF 135 
#define  MBOX_DIR_AFPF_UP 134 
#define  MBOX_DIR_PFAF 133 
#define  MBOX_DIR_PFAF_UP 132 
#define  MBOX_DIR_PFVF 131 
#define  MBOX_DIR_PFVF_UP 130 
#define  MBOX_DIR_VFPF 129 
#define  MBOX_DIR_VFPF_UP 128 
 void* MBOX_DOWN_RX_SIZE ; 
 void* MBOX_DOWN_RX_START ; 
 void* MBOX_DOWN_TX_SIZE ; 
 void* MBOX_DOWN_TX_START ; 
 int MBOX_SIZE ; 
 void* MBOX_UP_RX_SIZE ; 
 void* MBOX_UP_RX_START ; 
 void* MBOX_UP_TX_SIZE ; 
 void* MBOX_UP_TX_START ; 
 int /*<<< orphan*/  RVU_AF_AFPF_MBOX0 ; 
 int /*<<< orphan*/  RVU_PF_PFAF_MBOX1 ; 
 int /*<<< orphan*/  RVU_PF_VFX_PFVF_MBOX0 ; 
 int /*<<< orphan*/  RVU_VF_VFPF_MBOX1 ; 
 struct otx2_mbox_dev* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otx2_mbox_destroy (struct otx2_mbox*) ; 
 int /*<<< orphan*/  otx2_mbox_reset (struct otx2_mbox*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int otx2_mbox_init(struct otx2_mbox *mbox, void *hwbase, struct pci_dev *pdev,
		   void *reg_base, int direction, int ndevs)
{
	struct otx2_mbox_dev *mdev;
	int devid;

	switch (direction) {
	case MBOX_DIR_AFPF:
	case MBOX_DIR_PFVF:
		mbox->tx_start = MBOX_DOWN_TX_START;
		mbox->rx_start = MBOX_DOWN_RX_START;
		mbox->tx_size  = MBOX_DOWN_TX_SIZE;
		mbox->rx_size  = MBOX_DOWN_RX_SIZE;
		break;
	case MBOX_DIR_PFAF:
	case MBOX_DIR_VFPF:
		mbox->tx_start = MBOX_DOWN_RX_START;
		mbox->rx_start = MBOX_DOWN_TX_START;
		mbox->tx_size  = MBOX_DOWN_RX_SIZE;
		mbox->rx_size  = MBOX_DOWN_TX_SIZE;
		break;
	case MBOX_DIR_AFPF_UP:
	case MBOX_DIR_PFVF_UP:
		mbox->tx_start = MBOX_UP_TX_START;
		mbox->rx_start = MBOX_UP_RX_START;
		mbox->tx_size  = MBOX_UP_TX_SIZE;
		mbox->rx_size  = MBOX_UP_RX_SIZE;
		break;
	case MBOX_DIR_PFAF_UP:
	case MBOX_DIR_VFPF_UP:
		mbox->tx_start = MBOX_UP_RX_START;
		mbox->rx_start = MBOX_UP_TX_START;
		mbox->tx_size  = MBOX_UP_RX_SIZE;
		mbox->rx_size  = MBOX_UP_TX_SIZE;
		break;
	default:
		return -ENODEV;
	}

	switch (direction) {
	case MBOX_DIR_AFPF:
	case MBOX_DIR_AFPF_UP:
		mbox->trigger = RVU_AF_AFPF_MBOX0;
		mbox->tr_shift = 4;
		break;
	case MBOX_DIR_PFAF:
	case MBOX_DIR_PFAF_UP:
		mbox->trigger = RVU_PF_PFAF_MBOX1;
		mbox->tr_shift = 0;
		break;
	case MBOX_DIR_PFVF:
	case MBOX_DIR_PFVF_UP:
		mbox->trigger = RVU_PF_VFX_PFVF_MBOX0;
		mbox->tr_shift = 12;
		break;
	case MBOX_DIR_VFPF:
	case MBOX_DIR_VFPF_UP:
		mbox->trigger = RVU_VF_VFPF_MBOX1;
		mbox->tr_shift = 0;
		break;
	default:
		return -ENODEV;
	}

	mbox->reg_base = reg_base;
	mbox->hwbase = hwbase;
	mbox->pdev = pdev;

	mbox->dev = kcalloc(ndevs, sizeof(struct otx2_mbox_dev), GFP_KERNEL);
	if (!mbox->dev) {
		otx2_mbox_destroy(mbox);
		return -ENOMEM;
	}

	mbox->ndevs = ndevs;
	for (devid = 0; devid < ndevs; devid++) {
		mdev = &mbox->dev[devid];
		mdev->mbase = mbox->hwbase + (devid * MBOX_SIZE);
		spin_lock_init(&mdev->mbox_lock);
		/* Init header to reset value */
		otx2_mbox_reset(mbox, devid);
	}

	return 0;
}