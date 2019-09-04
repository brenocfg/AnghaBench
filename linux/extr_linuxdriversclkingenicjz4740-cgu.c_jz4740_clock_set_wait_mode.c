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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum jz4740_wait_mode { ____Placeholder_jz4740_wait_mode } jz4740_wait_mode ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CGU_REG_LCR ; 
#define  JZ4740_WAIT_MODE_IDLE 129 
#define  JZ4740_WAIT_MODE_SLEEP 128 
 int /*<<< orphan*/  LCR_SLEEP ; 
 TYPE_1__* cgu ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void jz4740_clock_set_wait_mode(enum jz4740_wait_mode mode)
{
	uint32_t lcr = readl(cgu->base + CGU_REG_LCR);

	switch (mode) {
	case JZ4740_WAIT_MODE_IDLE:
		lcr &= ~LCR_SLEEP;
		break;

	case JZ4740_WAIT_MODE_SLEEP:
		lcr |= LCR_SLEEP;
		break;
	}

	writel(lcr, cgu->base + CGU_REG_LCR);
}