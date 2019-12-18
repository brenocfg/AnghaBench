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
struct ir_raw_event {scalar_t__ pulse; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_transition(struct ir_raw_event *x, struct ir_raw_event *y)
{
	return x->pulse != y->pulse;
}