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
typedef  scalar_t__ u16 ;
struct sdma_engine {scalar_t__ descq_cnt; } ;

/* Variables and functions */
 scalar_t__ sdma_descq_freecnt (struct sdma_engine*) ; 

__attribute__((used)) static inline u16 sdma_descq_inprocess(struct sdma_engine *sde)
{
	return sde->descq_cnt - sdma_descq_freecnt(sde);
}