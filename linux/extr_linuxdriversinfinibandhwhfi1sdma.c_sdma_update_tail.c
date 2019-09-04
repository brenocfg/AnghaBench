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
typedef  int /*<<< orphan*/  u16 ;
struct sdma_engine {int /*<<< orphan*/  tail_csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sdma_update_tail(struct sdma_engine *sde, u16 tail)
{
	/* Commit writes to memory and advance the tail on the chip */
	smp_wmb(); /* see get_txhead() */
	writeq(tail, sde->tail_csr);
}