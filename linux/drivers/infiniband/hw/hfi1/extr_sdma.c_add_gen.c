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
typedef  int u8 ;
typedef  int u64 ;
struct sdma_engine {int descq_tail; int sdma_shift; } ;

/* Variables and functions */
 int SDMA_DESC1_GENERATION_MASK ; 
 int SDMA_DESC1_GENERATION_SHIFT ; 
 int SDMA_DESC1_GENERATION_SMASK ; 

__attribute__((used)) static inline u64 add_gen(struct sdma_engine *sde, u64 qw1)
{
	u8 generation = (sde->descq_tail >> sde->sdma_shift) & 3;

	qw1 &= ~SDMA_DESC1_GENERATION_SMASK;
	qw1 |= ((u64)generation & SDMA_DESC1_GENERATION_MASK)
			<< SDMA_DESC1_GENERATION_SHIFT;
	return qw1;
}