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
struct dm_cache_policy {int (* set_config_value ) (struct dm_cache_policy*,char const*,char const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct dm_cache_policy*,char const*,char const*) ; 

__attribute__((used)) static inline int policy_set_config_value(struct dm_cache_policy *p,
					  const char *key, const char *value)
{
	return p->set_config_value ? p->set_config_value(p, key, value) : -EINVAL;
}