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
struct governor_attr {int /*<<< orphan*/  (* show ) (int /*<<< orphan*/ ,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 struct governor_attr* to_gov_attr (struct attribute*) ; 
 int /*<<< orphan*/  to_gov_attr_set (struct kobject*) ; 

__attribute__((used)) static ssize_t governor_show(struct kobject *kobj, struct attribute *attr,
			     char *buf)
{
	struct governor_attr *gattr = to_gov_attr(attr);

	return gattr->show(to_gov_attr_set(kobj), buf);
}