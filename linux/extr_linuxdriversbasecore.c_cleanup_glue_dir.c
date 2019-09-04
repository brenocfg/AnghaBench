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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdp_mutex ; 
 int /*<<< orphan*/  kobject_del (struct kobject*) ; 
 int /*<<< orphan*/  kobject_has_children (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  live_in_glue_dir (struct kobject*,struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_glue_dir(struct device *dev, struct kobject *glue_dir)
{
	/* see if we live in a "glue" directory */
	if (!live_in_glue_dir(glue_dir, dev))
		return;

	mutex_lock(&gdp_mutex);
	if (!kobject_has_children(glue_dir))
		kobject_del(glue_dir);
	kobject_put(glue_dir);
	mutex_unlock(&gdp_mutex);
}