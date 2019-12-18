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
struct bus_type {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 long RIO_MAX_MPORTS ; 
 long RIO_MPORT_ANY ; 
 scalar_t__ kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int rio_init_mports () ; 
 int rio_mport_scan (int) ; 

__attribute__((used)) static ssize_t scan_store(struct bus_type *bus, const char *buf, size_t count)
{
	long val;
	int rc;

	if (kstrtol(buf, 0, &val) < 0)
		return -EINVAL;

	if (val == RIO_MPORT_ANY) {
		rc = rio_init_mports();
		goto exit;
	}

	if (val < 0 || val >= RIO_MAX_MPORTS)
		return -EINVAL;

	rc = rio_mport_scan((int)val);
exit:
	if (!rc)
		rc = count;

	return rc;
}