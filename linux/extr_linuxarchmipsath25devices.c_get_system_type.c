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

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 size_t ATH25_SOC_UNKNOWN ; 
 size_t ath25_soc ; 
 char const** soc_type_strings ; 

const char *get_system_type(void)
{
	if ((ath25_soc >= ARRAY_SIZE(soc_type_strings)) ||
	    !soc_type_strings[ath25_soc])
		return soc_type_strings[ATH25_SOC_UNKNOWN];
	return soc_type_strings[ath25_soc];
}