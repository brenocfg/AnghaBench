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
struct bus_type {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  aqm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DOMAINS ; 
 int /*<<< orphan*/  ap_bus_revise_bindings () ; 
 int ap_parse_mask_str (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 

__attribute__((used)) static ssize_t aqmask_store(struct bus_type *bus, const char *buf,
			    size_t count)
{
	int rc;

	rc = ap_parse_mask_str(buf, ap_perms.aqm, AP_DOMAINS, &ap_perms_mutex);
	if (rc)
		return rc;

	ap_bus_revise_bindings();

	return count;
}