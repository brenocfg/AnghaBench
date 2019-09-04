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
struct qlcnic_host_sds_ring {int /*<<< orphan*/  napi; struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {int dummy; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_clear_legacy_intr (struct qlcnic_adapter*) ; 

__attribute__((used)) static irqreturn_t qlcnic_intr(int irq, void *data)
{
	struct qlcnic_host_sds_ring *sds_ring = data;
	struct qlcnic_adapter *adapter = sds_ring->adapter;

	if (qlcnic_clear_legacy_intr(adapter) == IRQ_NONE)
		return IRQ_NONE;

	napi_schedule(&sds_ring->napi);

	return IRQ_HANDLED;
}