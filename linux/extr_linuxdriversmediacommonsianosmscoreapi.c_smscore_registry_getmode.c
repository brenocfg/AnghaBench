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
struct smscore_registry_entry_t {int mode; } ;

/* Variables and functions */
 int default_mode ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct smscore_registry_entry_t* smscore_find_registry (char*) ; 

int smscore_registry_getmode(char *devpath)
{
	struct smscore_registry_entry_t *entry;

	entry = smscore_find_registry(devpath);
	if (entry)
		return entry->mode;
	else
		pr_err("No registry found.\n");

	return default_mode;
}