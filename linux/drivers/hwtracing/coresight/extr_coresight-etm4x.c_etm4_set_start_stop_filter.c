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
struct etmv4_config {int* addr_type; int /*<<< orphan*/  vissctlr; void** addr_acc; void** addr_val; } ;
typedef  enum etm_addr_type { ____Placeholder_etm_addr_type } etm_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ETM_ADDR_TYPE_START ; 
 void* etm4_get_access_type (struct etmv4_config*) ; 

__attribute__((used)) static void etm4_set_start_stop_filter(struct etmv4_config *config,
				       u64 address, int comparator,
				       enum etm_addr_type type)
{
	int shift;
	u64 access_type = etm4_get_access_type(config);

	/* Configure the comparator */
	config->addr_val[comparator] = address;
	config->addr_acc[comparator] = access_type;
	config->addr_type[comparator] = type;

	/*
	 * Configure ViewInst Start-Stop control register.
	 * Addresses configured to start tracing go from bit 0 to n-1,
	 * while those configured to stop tracing from 16 to 16 + n-1.
	 */
	shift = (type == ETM_ADDR_TYPE_START ? 0 : 16);
	config->vissctlr |= BIT(shift + comparator);
}