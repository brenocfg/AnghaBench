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
struct hinic_ceqs {struct hinic_ceq_cb* ceq_cb; struct hinic_hwif* hwif; } ;
struct hinic_ceq_cb {unsigned long ceqe_state; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum hinic_ceq_type { ____Placeholder_hinic_ceq_type } hinic_ceq_type ;

/* Variables and functions */
 int /*<<< orphan*/  CEQE_DATA (int /*<<< orphan*/ ) ; 
 int CEQE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned long HINIC_EQE_ENABLED ; 
 unsigned long HINIC_EQE_RUNNING ; 
 int HINIC_MAX_CEQ_EVENTS ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ceq_event_handler(struct hinic_ceqs *ceqs, u32 ceqe)
{
	struct hinic_hwif *hwif = ceqs->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_ceq_cb *ceq_cb;
	enum hinic_ceq_type event;
	unsigned long eqe_state;

	event = CEQE_TYPE(ceqe);
	if (event >= HINIC_MAX_CEQ_EVENTS) {
		dev_err(&pdev->dev, "Unknown CEQ event, event = %d\n", event);
		return;
	}

	ceq_cb = &ceqs->ceq_cb[event];

	eqe_state = cmpxchg(&ceq_cb->ceqe_state,
			    HINIC_EQE_ENABLED,
			    HINIC_EQE_ENABLED | HINIC_EQE_RUNNING);

	if ((eqe_state == HINIC_EQE_ENABLED) && (ceq_cb->handler))
		ceq_cb->handler(ceq_cb->handle, CEQE_DATA(ceqe));
	else
		dev_err(&pdev->dev, "Unhandled CEQ Event %d\n", event);

	ceq_cb->ceqe_state &= ~HINIC_EQE_RUNNING;
}