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
typedef  scalar_t__ u32 ;
struct lpc32xx_irq_chip {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void lpc32xx_ic_write(struct lpc32xx_irq_chip *ic,
				    u32 reg, u32 val)
{
	writel_relaxed(val, ic->base + reg);
}