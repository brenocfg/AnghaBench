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
struct gru_instruction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gru_flush_cache (struct gru_instruction*) ; 
 int /*<<< orphan*/  gru_ordered_store_ulong (struct gru_instruction*,unsigned long) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void gru_start_instruction(struct gru_instruction *ins, unsigned long op64)
{
	gru_ordered_store_ulong(ins, op64);
	mb();
	gru_flush_cache(ins);
}