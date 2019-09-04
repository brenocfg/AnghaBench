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
struct policy_dbs_info {int dummy; } ;
struct cs_policy_dbs_info {struct policy_dbs_info policy_dbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cs_policy_dbs_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct policy_dbs_info *cs_alloc(void)
{
	struct cs_policy_dbs_info *dbs_info;

	dbs_info = kzalloc(sizeof(*dbs_info), GFP_KERNEL);
	return dbs_info ? &dbs_info->policy_dbs : NULL;
}