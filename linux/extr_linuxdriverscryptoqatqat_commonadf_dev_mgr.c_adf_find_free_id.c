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
 unsigned int ADF_MAX_DEVICES ; 
 int* id_map ; 

__attribute__((used)) static unsigned int adf_find_free_id(void)
{
	unsigned int i;

	for (i = 0; i < ADF_MAX_DEVICES; i++) {
		if (!id_map[i]) {
			id_map[i] = 1;
			return i;
		}
	}
	return ADF_MAX_DEVICES + 1;
}