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
struct elog_obj {int /*<<< orphan*/  type; } ;
struct elog_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  elog_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t elog_type_show(struct elog_obj *elog_obj,
			      struct elog_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "0x%llx %s\n",
		       elog_obj->type,
		       elog_type_to_string(elog_obj->type));
}