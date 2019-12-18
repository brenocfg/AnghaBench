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
 int ARRAY_SIZE (char**) ; 
 int driver_byte (int) ; 
 char** driverbyte_table ; 

const char *scsi_driverbyte_string(int result)
{
	const char *db_string = NULL;
	int db = driver_byte(result);

	if (db < ARRAY_SIZE(driverbyte_table))
		db_string = driverbyte_table[db];
	return db_string;
}