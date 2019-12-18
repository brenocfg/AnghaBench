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
typedef  int /*<<< orphan*/  u64 ;
struct cxl {TYPE_2__* native; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* sl_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* err_irq_dump_registers ) (struct cxl*) ;int /*<<< orphan*/  (* debugfs_stop_trace ) (struct cxl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_ErrIVTE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct cxl*) ; 
 int /*<<< orphan*/  stub2 (struct cxl*) ; 

__attribute__((used)) static irqreturn_t native_irq_err(int irq, void *data)
{
	struct cxl *adapter = data;
	u64 err_ivte;

	WARN(1, "CXL ERROR interrupt %i\n", irq);

	err_ivte = cxl_p1_read(adapter, CXL_PSL_ErrIVTE);
	dev_crit(&adapter->dev, "PSL_ErrIVTE: 0x%016llx\n", err_ivte);

	if (adapter->native->sl_ops->debugfs_stop_trace) {
		dev_crit(&adapter->dev, "STOPPING CXL TRACE\n");
		adapter->native->sl_ops->debugfs_stop_trace(adapter);
	}

	if (adapter->native->sl_ops->err_irq_dump_registers)
		adapter->native->sl_ops->err_irq_dump_registers(adapter);

	return IRQ_HANDLED;
}