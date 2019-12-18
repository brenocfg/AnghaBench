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
struct etmv4_config {int dummy; } ;

/* Variables and functions */
 int ETM_EXLEVEL_S_APP ; 
 int ETM_EXLEVEL_S_HYP ; 
 int ETM_EXLEVEL_S_OS ; 
 int etm4_get_ns_access_type (struct etmv4_config*) ; 

__attribute__((used)) static u64 etm4_get_access_type(struct etmv4_config *config)
{
	u64 access_type = etm4_get_ns_access_type(config);

	/*
	 * EXLEVEL_S, bits[11:8], don't trace anything happening
	 * in secure state.
	 */
	access_type |= (ETM_EXLEVEL_S_APP	|
			ETM_EXLEVEL_S_OS	|
			ETM_EXLEVEL_S_HYP);

	return access_type;
}