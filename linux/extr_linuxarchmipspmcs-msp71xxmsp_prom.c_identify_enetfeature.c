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
 char FEATURE_NOEXIST ; 
 char* get_features () ; 

__attribute__((used)) static char identify_enetfeature(char key, unsigned long interface_num)
{
	char *feature = get_features();

	while (*feature) {
		if (*feature++ == key && interface_num-- == 0)
			return *feature;
		feature++;
	}

	return FEATURE_NOEXIST;
}