#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_audio_manager_module_attribute {int dummy; } ;
struct TYPE_2__ {char* name; } ;
struct gb_audio_manager_module {TYPE_1__ desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t gb_audio_module_name_show(
	struct gb_audio_manager_module *module,
	struct gb_audio_manager_module_attribute *attr, char *buf)
{
	return sprintf(buf, "%s", module->desc.name);
}