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
struct flexcop_device {size_t dev_type; size_t bus_type; size_t rev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * flexcop_bus_names ; 
 int /*<<< orphan*/ * flexcop_device_names ; 
 int /*<<< orphan*/ * flexcop_revision_names ; 
 int /*<<< orphan*/  info (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void flexcop_device_name(struct flexcop_device *fc,
		const char *prefix, const char *suffix)
{
	info("%s '%s' at the '%s' bus controlled by a '%s' %s",
			prefix,	flexcop_device_names[fc->dev_type],
			flexcop_bus_names[fc->bus_type],
			flexcop_revision_names[fc->rev], suffix);
}