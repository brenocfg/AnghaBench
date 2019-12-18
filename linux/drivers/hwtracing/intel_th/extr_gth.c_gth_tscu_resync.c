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
struct gth_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_TSCU_TSUCTRL ; 
 int /*<<< orphan*/  TSUCTRL_CTCRESYNC ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gth_tscu_resync(struct gth_device *gth)
{
	u32 reg;

	reg = ioread32(gth->base + REG_TSCU_TSUCTRL);
	reg &= ~TSUCTRL_CTCRESYNC;
	iowrite32(reg, gth->base + REG_TSCU_TSUCTRL);
}