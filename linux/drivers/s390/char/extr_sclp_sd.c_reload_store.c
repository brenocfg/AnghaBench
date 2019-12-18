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
struct sclp_sd_file {int dummy; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sclp_sd_file_update (struct sclp_sd_file*) ; 
 struct sclp_sd_file* to_sd_file (struct kobject*) ; 

__attribute__((used)) static ssize_t reload_store(struct kobject *kobj, struct kobj_attribute *attr,
			    const char *buf, size_t count)
{
	struct sclp_sd_file *sd_file = to_sd_file(kobj);

	sclp_sd_file_update(sd_file);

	return count;
}