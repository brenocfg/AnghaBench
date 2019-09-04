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
typedef  void* u64 ;
struct etmv4_config {int /*<<< orphan*/  viiectlr; void** addr_type; void** addr_acc; void** addr_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 void* ETM_ADDR_TYPE_RANGE ; 
 void* etm4_get_access_type (struct etmv4_config*) ; 

__attribute__((used)) static void etm4_set_comparator_filter(struct etmv4_config *config,
				       u64 start, u64 stop, int comparator)
{
	u64 access_type = etm4_get_access_type(config);

	/* First half of default address comparator */
	config->addr_val[comparator] = start;
	config->addr_acc[comparator] = access_type;
	config->addr_type[comparator] = ETM_ADDR_TYPE_RANGE;

	/* Second half of default address comparator */
	config->addr_val[comparator + 1] = stop;
	config->addr_acc[comparator + 1] = access_type;
	config->addr_type[comparator + 1] = ETM_ADDR_TYPE_RANGE;

	/*
	 * Configure the ViewInst function to include this address range
	 * comparator.
	 *
	 * @comparator is divided by two since it is the index in the
	 * etmv4_config::addr_val array but register TRCVIIECTLR deals with
	 * address range comparator _pairs_.
	 *
	 * Therefore:
	 *	index 0 -> compatator pair 0
	 *	index 2 -> comparator pair 1
	 *	index 4 -> comparator pair 2
	 *	...
	 *	index 14 -> comparator pair 7
	 */
	config->viiectlr |= BIT(comparator / 2);
}