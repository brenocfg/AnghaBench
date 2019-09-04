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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct applesmc_entry {int len; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct applesmc_entry const*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct applesmc_entry const*) ; 
 struct applesmc_entry* applesmc_get_entry_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_at_index ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t applesmc_key_at_index_data_length_show(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	const struct applesmc_entry *entry;

	entry = applesmc_get_entry_by_index(key_at_index);
	if (IS_ERR(entry))
		return PTR_ERR(entry);

	return snprintf(sysfsbuf, PAGE_SIZE, "%d\n", entry->len);
}