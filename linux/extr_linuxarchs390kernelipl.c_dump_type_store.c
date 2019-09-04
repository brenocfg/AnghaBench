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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_CCW_STR ; 
 int /*<<< orphan*/  DUMP_FCP_STR ; 
 int /*<<< orphan*/  DUMP_NONE_STR ; 
 int /*<<< orphan*/  DUMP_TYPE_CCW ; 
 int /*<<< orphan*/  DUMP_TYPE_FCP ; 
 int /*<<< orphan*/  DUMP_TYPE_NONE ; 
 int EINVAL ; 
 int dump_set_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dump_type_store(struct kobject *kobj,
			       struct kobj_attribute *attr,
			       const char *buf, size_t len)
{
	int rc = -EINVAL;

	if (strncmp(buf, DUMP_NONE_STR, strlen(DUMP_NONE_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_NONE);
	else if (strncmp(buf, DUMP_CCW_STR, strlen(DUMP_CCW_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_CCW);
	else if (strncmp(buf, DUMP_FCP_STR, strlen(DUMP_FCP_STR)) == 0)
		rc = dump_set_type(DUMP_TYPE_FCP);
	return (rc != 0) ? rc : len;
}