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
struct sdma_engine {scalar_t__ descq_tail; scalar_t__ descq_head; } ;

/* Variables and functions */

__attribute__((used)) static inline int sdma_empty(struct sdma_engine *sde)
{
	return sde->descq_tail == sde->descq_head;
}