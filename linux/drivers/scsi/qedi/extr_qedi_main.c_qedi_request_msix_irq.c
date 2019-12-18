#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_11__ {TYPE_4__* msix; int /*<<< orphan*/  used_cnt; } ;
struct TYPE_7__ {int num_hwfns; } ;
struct TYPE_8__ {TYPE_1__ common; } ;
struct qedi_ctx {TYPE_5__ int_info; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/ * fp_array; int /*<<< orphan*/  cdev; TYPE_2__ dev_info; } ;
struct TYPE_12__ {TYPE_3__* common; } ;
struct TYPE_10__ {int /*<<< orphan*/  vector; } ;
struct TYPE_9__ {size_t (* get_affin_hwfn_idx ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MIN_NUM_CPUS_MSIX (struct qedi_ctx*) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu_mask (int) ; 
 int irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_msix_handler ; 
 TYPE_6__* qedi_ops ; 
 int /*<<< orphan*/  qedi_sync_free_irqs (struct qedi_ctx*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 
 size_t stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_request_msix_irq(struct qedi_ctx *qedi)
{
	int i, rc, cpu;
	u16 idx;

	cpu = cpumask_first(cpu_online_mask);
	for (i = 0; i < MIN_NUM_CPUS_MSIX(qedi); i++) {
		idx = i * qedi->dev_info.common.num_hwfns +
			  qedi_ops->common->get_affin_hwfn_idx(qedi->cdev);

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "dev_info: num_hwfns=%d affin_hwfn_idx=%d.\n",
			  qedi->dev_info.common.num_hwfns,
			  qedi_ops->common->get_affin_hwfn_idx(qedi->cdev));

		rc = request_irq(qedi->int_info.msix[idx].vector,
				 qedi_msix_handler, 0, "qedi",
				 &qedi->fp_array[i]);
		if (rc) {
			QEDI_WARN(&qedi->dbg_ctx, "request_irq failed.\n");
			qedi_sync_free_irqs(qedi);
			return rc;
		}
		qedi->int_info.used_cnt++;
		rc = irq_set_affinity_hint(qedi->int_info.msix[idx].vector,
					   get_cpu_mask(cpu));
		cpu = cpumask_next(cpu, cpu_online_mask);
	}

	return 0;
}