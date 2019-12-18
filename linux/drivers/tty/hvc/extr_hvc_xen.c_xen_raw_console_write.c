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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
 int dom0_write_console (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ xen_domain () ; 
 int /*<<< orphan*/  xen_hvm_domain () ; 
 int /*<<< orphan*/  xen_hvm_early_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void xen_raw_console_write(const char *str)
{
	ssize_t len = strlen(str);
	int rc = 0;

	if (xen_domain()) {
		rc = dom0_write_console(0, str, len);
		if (rc != -ENOSYS || !xen_hvm_domain())
			return;
	}
	xen_hvm_early_write(0, str, len);
}