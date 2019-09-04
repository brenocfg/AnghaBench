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
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_aml_initialized ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  acpi_aml_kern_writable () ; 
 int acpi_aml_write_kern (char const*,int) ; 
 int strlen (char const*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t acpi_aml_write_log(const char *msg)
{
	int ret = 0;
	int count = 0, size = 0;

	if (!acpi_aml_initialized)
		return -ENODEV;
	if (msg)
		count = strlen(msg);
	while (count > 0) {
again:
		ret = acpi_aml_write_kern(msg + size, count);
		if (ret == -EAGAIN) {
			ret = wait_event_interruptible(acpi_aml_io.wait,
				acpi_aml_kern_writable());
			/*
			 * We need to retry when the condition
			 * becomes true.
			 */
			if (ret == 0)
				goto again;
			break;
		}
		if (ret < 0)
			break;
		size += ret;
		count -= ret;
	}
	return size > 0 ? size : ret;
}