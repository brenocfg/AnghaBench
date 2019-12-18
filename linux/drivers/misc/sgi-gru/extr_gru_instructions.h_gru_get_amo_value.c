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
struct gru_instruction {unsigned long avalue; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long gru_get_amo_value(void *cb)
{
	struct gru_instruction *ins = (void *)cb;

	return ins->avalue;
}