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
 int /*<<< orphan*/  DM_RESERVED_MAX_IOS ; 
 int /*<<< orphan*/  RESERVED_REQUEST_BASED_IOS ; 
 int __dm_get_module_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserved_rq_based_ios ; 

unsigned dm_get_reserved_rq_based_ios(void)
{
	return __dm_get_module_param(&reserved_rq_based_ios,
				     RESERVED_REQUEST_BASED_IOS, DM_RESERVED_MAX_IOS);
}