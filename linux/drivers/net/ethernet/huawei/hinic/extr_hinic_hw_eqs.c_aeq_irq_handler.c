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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hw_event_cb {unsigned long hwe_state; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* hwe_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct hinic_eq {int q_len; int wrapped; int cons_idx; } ;
struct hinic_aeqs {struct hinic_hw_event_cb* hwe_cb; struct hinic_hwif* hwif; } ;
struct hinic_aeq_elem {int /*<<< orphan*/  data; int /*<<< orphan*/  desc; } ;
typedef  enum hinic_aeq_type { ____Placeholder_hinic_aeq_type } hinic_aeq_type ;

/* Variables and functions */
 struct hinic_aeq_elem* GET_CURR_AEQ_ELEM (struct hinic_eq*) ; 
 unsigned long HINIC_EQE_ENABLED ; 
 unsigned long HINIC_EQE_RUNNING ; 
 int HINIC_EQ_ELEM_DESC_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HINIC_MAX_AEQ_EVENTS ; 
 int /*<<< orphan*/  SIZE ; 
 int /*<<< orphan*/  SRC ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  WRAPPED ; 
 struct hinic_aeqs* aeq_to_aeqs (struct hinic_eq*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aeq_irq_handler(struct hinic_eq *eq)
{
	struct hinic_aeqs *aeqs = aeq_to_aeqs(eq);
	struct hinic_hwif *hwif = aeqs->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_aeq_elem *aeqe_curr;
	struct hinic_hw_event_cb *hwe_cb;
	enum hinic_aeq_type event;
	unsigned long eqe_state;
	u32 aeqe_desc;
	int i, size;

	for (i = 0; i < eq->q_len; i++) {
		aeqe_curr = GET_CURR_AEQ_ELEM(eq);

		/* Data in HW is in Big endian Format */
		aeqe_desc = be32_to_cpu(aeqe_curr->desc);

		/* HW toggles the wrapped bit, when it adds eq element */
		if (HINIC_EQ_ELEM_DESC_GET(aeqe_desc, WRAPPED) == eq->wrapped)
			break;

		event = HINIC_EQ_ELEM_DESC_GET(aeqe_desc, TYPE);
		if (event >= HINIC_MAX_AEQ_EVENTS) {
			dev_err(&pdev->dev, "Unknown AEQ Event %d\n", event);
			return;
		}

		if (!HINIC_EQ_ELEM_DESC_GET(aeqe_desc, SRC)) {
			hwe_cb = &aeqs->hwe_cb[event];

			size = HINIC_EQ_ELEM_DESC_GET(aeqe_desc, SIZE);

			eqe_state = cmpxchg(&hwe_cb->hwe_state,
					    HINIC_EQE_ENABLED,
					    HINIC_EQE_ENABLED |
					    HINIC_EQE_RUNNING);
			if ((eqe_state == HINIC_EQE_ENABLED) &&
			    (hwe_cb->hwe_handler))
				hwe_cb->hwe_handler(hwe_cb->handle,
						    aeqe_curr->data, size);
			else
				dev_err(&pdev->dev, "Unhandled AEQ Event %d\n",
					event);

			hwe_cb->hwe_state &= ~HINIC_EQE_RUNNING;
		}

		eq->cons_idx++;

		if (eq->cons_idx == eq->q_len) {
			eq->cons_idx = 0;
			eq->wrapped = !eq->wrapped;
		}
	}
}