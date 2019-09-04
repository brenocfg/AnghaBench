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
typedef  enum cpumf_ctr_set { ____Placeholder_cpumf_ctr_set } cpumf_ctr_set ;

/* Variables and functions */
 int CPUMF_CTR_SET_BASIC ; 
 int CPUMF_CTR_SET_CRYPTO ; 
 int CPUMF_CTR_SET_EXT ; 
 int CPUMF_CTR_SET_MAX ; 
 int CPUMF_CTR_SET_MT_DIAG ; 
 int CPUMF_CTR_SET_USER ; 

__attribute__((used)) static enum cpumf_ctr_set get_counter_set(u64 event)
{
	int set = CPUMF_CTR_SET_MAX;

	if (event < 32)
		set = CPUMF_CTR_SET_BASIC;
	else if (event < 64)
		set = CPUMF_CTR_SET_USER;
	else if (event < 128)
		set = CPUMF_CTR_SET_CRYPTO;
	else if (event < 256)
		set = CPUMF_CTR_SET_EXT;
	else if (event >= 448 && event < 496)
		set = CPUMF_CTR_SET_MT_DIAG;

	return set;
}