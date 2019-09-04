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

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 

__attribute__((used)) static inline void fw_cfg_kobj_cleanup(struct kobject *kobj)
{
	kobject_del(kobj);
	kobject_put(kobj);
}