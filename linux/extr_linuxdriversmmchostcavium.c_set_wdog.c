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
typedef  unsigned int u64 ;
struct cvm_mmc_slot {unsigned int clock; TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MIO_EMM_WDOG (TYPE_1__*) ; 
 unsigned int NSEC_PER_SEC ; 
 int /*<<< orphan*/  writeq (unsigned int,scalar_t__) ; 

__attribute__((used)) static void set_wdog(struct cvm_mmc_slot *slot, unsigned int ns)
{
	u64 timeout;

	if (!slot->clock)
		return;

	if (ns)
		timeout = (slot->clock * ns) / NSEC_PER_SEC;
	else
		timeout = (slot->clock * 850ull) / 1000ull;
	writeq(timeout, slot->host->base + MIO_EMM_WDOG(slot->host));
}