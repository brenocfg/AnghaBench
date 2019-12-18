#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hl_eqe_work {int /*<<< orphan*/  eq_work; int /*<<< orphan*/  eq_entry; struct hl_device* hdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctl; } ;
struct hl_eq_entry {TYPE_1__ hdr; } ;
struct hl_eq {size_t ci; scalar_t__ kernel_address; struct hl_device* hdev; } ;
struct hl_device {TYPE_2__* asic_funcs; int /*<<< orphan*/  eq_wq; int /*<<< orphan*/  dev; scalar_t__ disabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_eq_ci ) (struct hl_device*,size_t) ;} ;

/* Variables and functions */
 int EQ_CTL_READY_MASK ; 
 int EQ_CTL_READY_SHIFT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 size_t hl_eq_inc_ptr (size_t) ; 
 int /*<<< orphan*/  irq_handle_eqe ; 
 struct hl_eqe_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hl_eq_entry*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,size_t) ; 

irqreturn_t hl_irq_handler_eq(int irq, void *arg)
{
	struct hl_eq *eq = arg;
	struct hl_device *hdev = eq->hdev;
	struct hl_eq_entry *eq_entry;
	struct hl_eq_entry *eq_base;
	struct hl_eqe_work *handle_eqe_work;

	eq_base = (struct hl_eq_entry *) (uintptr_t) eq->kernel_address;

	while (1) {
		bool entry_ready =
			((le32_to_cpu(eq_base[eq->ci].hdr.ctl) &
				EQ_CTL_READY_MASK) >> EQ_CTL_READY_SHIFT);

		if (!entry_ready)
			break;

		eq_entry = &eq_base[eq->ci];

		/*
		 * Make sure we read EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		if (hdev->disabled) {
			dev_warn(hdev->dev,
				"Device disabled but received IRQ %d for EQ\n",
					irq);
			goto skip_irq;
		}

		handle_eqe_work = kmalloc(sizeof(*handle_eqe_work), GFP_ATOMIC);
		if (handle_eqe_work) {
			INIT_WORK(&handle_eqe_work->eq_work, irq_handle_eqe);
			handle_eqe_work->hdev = hdev;

			memcpy(&handle_eqe_work->eq_entry, eq_entry,
					sizeof(*eq_entry));

			queue_work(hdev->eq_wq, &handle_eqe_work->eq_work);
		}
skip_irq:
		/* Clear EQ entry ready bit */
		eq_entry->hdr.ctl =
			cpu_to_le32(le32_to_cpu(eq_entry->hdr.ctl) &
							~EQ_CTL_READY_MASK);

		eq->ci = hl_eq_inc_ptr(eq->ci);

		hdev->asic_funcs->update_eq_ci(hdev, eq->ci);
	}

	return IRQ_HANDLED;
}