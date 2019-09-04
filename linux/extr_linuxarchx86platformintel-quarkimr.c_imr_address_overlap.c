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
struct imr_regs {int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ imr_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int imr_address_overlap(phys_addr_t addr, struct imr_regs *imr)
{
	return addr >= imr_to_phys(imr->addr_lo) && addr <= imr_to_phys(imr->addr_hi);
}