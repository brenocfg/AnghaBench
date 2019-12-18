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
typedef  int /*<<< orphan*/  u32 ;
struct xiic_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xiic_irq_clr (struct xiic_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xiic_irq_en (struct xiic_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xiic_irq_clr_en(struct xiic_i2c *i2c, u32 mask)
{
	xiic_irq_clr(i2c, mask);
	xiic_irq_en(i2c, mask);
}