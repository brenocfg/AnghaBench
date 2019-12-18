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
struct qdio_irq {int nr_input_qs; } ;

/* Variables and functions */

__attribute__((used)) static inline int has_multiple_inq_on_dsci(struct qdio_irq *irq_ptr)
{
	return irq_ptr->nr_input_qs > 1;
}