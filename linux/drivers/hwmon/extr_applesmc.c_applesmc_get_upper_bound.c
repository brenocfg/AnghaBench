#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct applesmc_entry {int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int key_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct applesmc_entry const*) ; 
 int PTR_ERR (struct applesmc_entry const*) ; 
 struct applesmc_entry* applesmc_get_entry_by_index (int) ; 
 TYPE_1__ smcreg ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int applesmc_get_upper_bound(unsigned int *hi, const char *key)
{
	int begin = 0, end = smcreg.key_count;
	const struct applesmc_entry *entry;

	while (begin != end) {
		int middle = begin + (end - begin) / 2;
		entry = applesmc_get_entry_by_index(middle);
		if (IS_ERR(entry)) {
			*hi = smcreg.key_count;
			return PTR_ERR(entry);
		}
		if (strcmp(key, entry->key) < 0)
			end = middle;
		else
			begin = middle + 1;
	}

	*hi = begin;
	return 0;
}