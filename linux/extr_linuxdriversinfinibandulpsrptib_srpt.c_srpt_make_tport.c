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
struct target_fabric_configfs {int dummy; } ;
struct se_wwn {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct se_wwn* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ srpt_lookup_wwn (char const*) ; 

__attribute__((used)) static struct se_wwn *srpt_make_tport(struct target_fabric_configfs *tf,
				      struct config_group *group,
				      const char *name)
{
	return srpt_lookup_wwn(name) ? : ERR_PTR(-EINVAL);
}