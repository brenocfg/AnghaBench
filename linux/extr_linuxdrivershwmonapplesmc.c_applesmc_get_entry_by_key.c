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
struct applesmc_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct applesmc_entry const* ERR_PTR (int) ; 
 struct applesmc_entry const* applesmc_get_entry_by_index (int) ; 
 int applesmc_get_lower_bound (int*,char const*) ; 
 int applesmc_get_upper_bound (int*,char const*) ; 

__attribute__((used)) static const struct applesmc_entry *applesmc_get_entry_by_key(const char *key)
{
	int begin, end;
	int ret;

	ret = applesmc_get_lower_bound(&begin, key);
	if (ret)
		return ERR_PTR(ret);
	ret = applesmc_get_upper_bound(&end, key);
	if (ret)
		return ERR_PTR(ret);
	if (end - begin != 1)
		return ERR_PTR(-EINVAL);

	return applesmc_get_entry_by_index(begin);
}