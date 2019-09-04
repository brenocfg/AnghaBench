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
struct engine_info {size_t class; int /*<<< orphan*/  instance; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ INTEL_ENGINE_CS_MAX_NAME ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* intel_engine_classes ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sprint_engine_name(char *name, const struct engine_info *info)
{
	WARN_ON(snprintf(name, INTEL_ENGINE_CS_MAX_NAME, "%s%u",
			 intel_engine_classes[info->class].name,
			 info->instance) >= INTEL_ENGINE_CS_MAX_NAME);
}