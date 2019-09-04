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
 int /*<<< orphan*/  readl (unsigned int) ; 

__attribute__((used)) static inline u32 ipu_ic_read(struct ipu_ic *ic, unsigned offset)
{
	return readl(ic->priv->base + offset);
}