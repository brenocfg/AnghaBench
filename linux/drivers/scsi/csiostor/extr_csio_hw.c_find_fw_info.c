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
struct fw_info {int chip; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fw_info*) ; 
 struct fw_info* fw_info_array ; 

__attribute__((used)) static struct fw_info *find_fw_info(int chip)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fw_info_array); i++) {
		if (fw_info_array[i].chip == chip)
			return &fw_info_array[i];
	}
	return NULL;
}