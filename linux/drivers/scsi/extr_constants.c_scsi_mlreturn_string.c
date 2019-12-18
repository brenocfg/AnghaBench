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
struct value_name_pair {int value; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct value_name_pair*) ; 
 struct value_name_pair* scsi_mlreturn_arr ; 

const char *scsi_mlreturn_string(int result)
{
	const struct value_name_pair *arr = scsi_mlreturn_arr;
	int k;

	for (k = 0; k < ARRAY_SIZE(scsi_mlreturn_arr); ++k, ++arr) {
		if (result == arr->value)
			return arr->name;
	}
	return NULL;
}