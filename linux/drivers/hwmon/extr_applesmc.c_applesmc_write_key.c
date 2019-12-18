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
typedef  int /*<<< orphan*/  u8 ;
struct applesmc_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct applesmc_entry const*) ; 
 int PTR_ERR (struct applesmc_entry const*) ; 
 struct applesmc_entry* applesmc_get_entry_by_key (char const*) ; 
 int applesmc_write_entry (struct applesmc_entry const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int applesmc_write_key(const char *key, const u8 *buffer, u8 len)
{
	const struct applesmc_entry *entry;

	entry = applesmc_get_entry_by_key(key);
	if (IS_ERR(entry))
		return PTR_ERR(entry);

	return applesmc_write_entry(entry, buffer, len);
}