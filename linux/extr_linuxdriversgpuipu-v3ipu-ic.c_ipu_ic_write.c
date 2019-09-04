#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ipu_ic {TYPE_1__* priv; } ;
struct TYPE_2__ {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void ipu_ic_write(struct ipu_ic *ic, u32 value, unsigned offset)
{
	writel(value, ic->priv->base + offset);
}