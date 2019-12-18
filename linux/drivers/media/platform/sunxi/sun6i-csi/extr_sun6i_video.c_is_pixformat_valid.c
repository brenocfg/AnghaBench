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
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* supported_pixformats ; 

__attribute__((used)) static bool is_pixformat_valid(unsigned int pixformat)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(supported_pixformats); i++)
		if (supported_pixformats[i] == pixformat)
			return true;

	return false;
}