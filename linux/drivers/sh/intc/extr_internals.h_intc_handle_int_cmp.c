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
struct intc_handle_int {int irq; } ;

/* Variables and functions */

__attribute__((used)) static inline int intc_handle_int_cmp(const void *a, const void *b)
{
	const struct intc_handle_int *_a = a;
	const struct intc_handle_int *_b = b;

	return _a->irq - _b->irq;
}