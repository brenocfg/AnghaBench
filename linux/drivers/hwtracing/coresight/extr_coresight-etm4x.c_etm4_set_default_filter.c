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
typedef  int u64 ;
struct etmv4_config {int vissctlr; int /*<<< orphan*/  vinst_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ETM_DEFAULT_ADDR_COMP ; 
 int /*<<< orphan*/  etm4_set_comparator_filter (struct etmv4_config*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etm4_set_default_filter(struct etmv4_config *config)
{
	u64 start, stop;

	/*
	 * Configure address range comparator '0' to encompass all
	 * possible addresses.
	 */
	start = 0x0;
	stop = ~0x0;

	etm4_set_comparator_filter(config, start, stop,
				   ETM_DEFAULT_ADDR_COMP);

	/*
	 * TRCVICTLR::SSSTATUS == 1, the start-stop logic is
	 * in the started state
	 */
	config->vinst_ctrl |= BIT(9);

	/* No start-stop filtering for ViewInst */
	config->vissctlr = 0x0;
}