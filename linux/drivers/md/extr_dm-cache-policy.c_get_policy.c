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
struct dm_cache_policy_type {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dm_cache_policy_type*) ; 
 struct dm_cache_policy_type* get_policy_once (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

__attribute__((used)) static struct dm_cache_policy_type *get_policy(const char *name)
{
	struct dm_cache_policy_type *t;

	t = get_policy_once(name);
	if (IS_ERR(t))
		return NULL;

	if (t)
		return t;

	request_module("dm-cache-%s", name);

	t = get_policy_once(name);
	if (IS_ERR(t))
		return NULL;

	return t;
}