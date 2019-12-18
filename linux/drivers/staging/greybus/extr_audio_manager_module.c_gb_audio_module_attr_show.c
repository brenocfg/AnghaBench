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
struct gb_audio_manager_module_attribute {int /*<<< orphan*/  (* show ) (struct gb_audio_manager_module*,struct gb_audio_manager_module_attribute*,char*) ;} ;
struct gb_audio_manager_module {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct gb_audio_manager_module*,struct gb_audio_manager_module_attribute*,char*) ; 
 struct gb_audio_manager_module* to_gb_audio_module (struct kobject*) ; 
 struct gb_audio_manager_module_attribute* to_gb_audio_module_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t gb_audio_module_attr_show(struct kobject *kobj,
					 struct attribute *attr, char *buf)
{
	struct gb_audio_manager_module_attribute *attribute;
	struct gb_audio_manager_module *module;

	attribute = to_gb_audio_module_attr(attr);
	module = to_gb_audio_module(kobj);

	if (!attribute->show)
		return -EIO;

	return attribute->show(module, attribute, buf);
}