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
struct spacc_engine {scalar_t__ regs; } ;

/* Variables and functions */
 int SPA_FIFO_STAT_EMPTY ; 
 scalar_t__ SPA_FIFO_STAT_REG_OFFSET ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline int spacc_fifo_stat_empty(struct spacc_engine *engine)
{
	return readl(engine->regs + SPA_FIFO_STAT_REG_OFFSET) &
		SPA_FIFO_STAT_EMPTY;
}