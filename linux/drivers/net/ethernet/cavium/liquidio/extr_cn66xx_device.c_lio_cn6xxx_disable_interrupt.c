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
typedef  int /*<<< orphan*/  u8 ;
struct octeon_device {scalar_t__ chip; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  intr_enb_reg64; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lio_cn6xxx_disable_interrupt(struct octeon_device *oct,
				  u8 unused __attribute__((unused)))
{
	struct octeon_cn6xxx *cn6xxx = (struct octeon_cn6xxx *)oct->chip;

	/* Disable Interrupts */
	writeq(0, cn6xxx->intr_enb_reg64);
}