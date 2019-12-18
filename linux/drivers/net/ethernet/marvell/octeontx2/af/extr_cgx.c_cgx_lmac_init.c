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
struct lmac {int lmac_id; void* name; int /*<<< orphan*/  event_cb_lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  wq_cmd_cmplt; struct cgx* cgx; } ;
struct cgx {int lmac_count; int cgx_id; struct lmac** lmac_idmap; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGXX_CMRX_INT_ENA_W1S ; 
 int /*<<< orphan*/  CGXX_CMRX_RX_LMACS ; 
 scalar_t__ CGX_LMAC_FWI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CGX_INT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_LMAC_PER_CGX ; 
 int /*<<< orphan*/  cgx_fwi_event_handler ; 
 int cgx_lmac_verify_fwi_version (struct cgx*) ; 
 int cgx_read (struct cgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgx_write (struct cgx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct lmac*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (void*,char*,int,int) ; 

__attribute__((used)) static int cgx_lmac_init(struct cgx *cgx)
{
	struct lmac *lmac;
	int i, err;

	cgx->lmac_count = cgx_read(cgx, 0, CGXX_CMRX_RX_LMACS) & 0x7;
	if (cgx->lmac_count > MAX_LMAC_PER_CGX)
		cgx->lmac_count = MAX_LMAC_PER_CGX;

	for (i = 0; i < cgx->lmac_count; i++) {
		lmac = kcalloc(1, sizeof(struct lmac), GFP_KERNEL);
		if (!lmac)
			return -ENOMEM;
		lmac->name = kcalloc(1, sizeof("cgx_fwi_xxx_yyy"), GFP_KERNEL);
		if (!lmac->name)
			return -ENOMEM;
		sprintf(lmac->name, "cgx_fwi_%d_%d", cgx->cgx_id, i);
		lmac->lmac_id = i;
		lmac->cgx = cgx;
		init_waitqueue_head(&lmac->wq_cmd_cmplt);
		mutex_init(&lmac->cmd_lock);
		spin_lock_init(&lmac->event_cb_lock);
		err = request_irq(pci_irq_vector(cgx->pdev,
						 CGX_LMAC_FWI + i * 9),
				   cgx_fwi_event_handler, 0, lmac->name, lmac);
		if (err)
			return err;

		/* Enable interrupt */
		cgx_write(cgx, lmac->lmac_id, CGXX_CMRX_INT_ENA_W1S,
			  FW_CGX_INT);

		/* Add reference */
		cgx->lmac_idmap[i] = lmac;
	}

	return cgx_lmac_verify_fwi_version(cgx);
}