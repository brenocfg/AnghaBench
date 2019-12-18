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
struct TYPE_6__ {unsigned long isliba; unsigned long osliba; int /*<<< orphan*/  ebcnam; int /*<<< orphan*/  qfmt; int /*<<< orphan*/  rflags; } ;
struct qdio_irq {TYPE_3__ qib; TYPE_2__** output_qs; TYPE_1__** input_qs; } ;
struct qdio_initialize {int /*<<< orphan*/  adapter_name; scalar_t__ no_output_qs; scalar_t__ no_input_qs; int /*<<< orphan*/  q_format; int /*<<< orphan*/  qib_rflags; } ;
struct TYPE_5__ {scalar_t__ slib; } ;
struct TYPE_4__ {scalar_t__ slib; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_RFLAGS_ENABLE_QEBSM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qebsm_possible () ; 

__attribute__((used)) static void setup_qib(struct qdio_irq *irq_ptr,
		      struct qdio_initialize *init_data)
{
	if (qebsm_possible())
		irq_ptr->qib.rflags |= QIB_RFLAGS_ENABLE_QEBSM;

	irq_ptr->qib.rflags |= init_data->qib_rflags;

	irq_ptr->qib.qfmt = init_data->q_format;
	if (init_data->no_input_qs)
		irq_ptr->qib.isliba =
			(unsigned long)(irq_ptr->input_qs[0]->slib);
	if (init_data->no_output_qs)
		irq_ptr->qib.osliba =
			(unsigned long)(irq_ptr->output_qs[0]->slib);
	memcpy(irq_ptr->qib.ebcnam, init_data->adapter_name, 8);
}