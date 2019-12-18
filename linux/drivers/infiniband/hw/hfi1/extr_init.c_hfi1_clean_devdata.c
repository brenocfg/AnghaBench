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
struct TYPE_2__ {int /*<<< orphan*/  rdi; } ;
struct hfi1_devdata {TYPE_1__ verbs_dev; int /*<<< orphan*/  num_sdma; int /*<<< orphan*/ * comp_vect; int /*<<< orphan*/ * tx_opstats; int /*<<< orphan*/ * send_schedule; int /*<<< orphan*/ * rcv_limit; int /*<<< orphan*/ * int_counter; int /*<<< orphan*/  unit; } ;
struct hfi1_asic_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_asic_data (struct hfi1_devdata*,struct hfi1_asic_data*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_platform_config (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_dev_table ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 struct hfi1_asic_data* release_asic_data (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  rvt_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_clean (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hfi1_clean_devdata(struct hfi1_devdata *dd)
{
	struct hfi1_asic_data *ad;
	unsigned long flags;

	xa_lock_irqsave(&hfi1_dev_table, flags);
	__xa_erase(&hfi1_dev_table, dd->unit);
	ad = release_asic_data(dd);
	xa_unlock_irqrestore(&hfi1_dev_table, flags);

	finalize_asic_data(dd, ad);
	free_platform_config(dd);
	rcu_barrier(); /* wait for rcu callbacks to complete */
	free_percpu(dd->int_counter);
	free_percpu(dd->rcv_limit);
	free_percpu(dd->send_schedule);
	free_percpu(dd->tx_opstats);
	dd->int_counter   = NULL;
	dd->rcv_limit     = NULL;
	dd->send_schedule = NULL;
	dd->tx_opstats    = NULL;
	kfree(dd->comp_vect);
	dd->comp_vect = NULL;
	sdma_clean(dd, dd->num_sdma);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
}