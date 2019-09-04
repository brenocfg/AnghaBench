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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  acpi_aml_initialized ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  acpi_aml_kern_readable () ; 
 int acpi_aml_readb_kern () ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t acpi_aml_read_cmd(char *msg, size_t count)
{
	int ret = 0;
	int size = 0;

	/*
	 * This is ensured by the running fact of the debugger thread
	 * unless a bug is introduced.
	 */
	BUG_ON(!acpi_aml_initialized);
	while (count > 0) {
again:
		/*
		 * Check each input byte to find the end of the command.
		 */
		ret = acpi_aml_readb_kern();
		if (ret == -EAGAIN) {
			ret = wait_event_interruptible(acpi_aml_io.wait,
				acpi_aml_kern_readable());
			/*
			 * We need to retry when the condition becomes
			 * true.
			 */
			if (ret == 0)
				goto again;
		}
		if (ret < 0)
			break;
		*(msg + size) = (char)ret;
		size++;
		count--;
		if (ret == '\n') {
			/*
			 * acpi_os_get_line() requires a zero terminated command
			 * string.
			 */
			*(msg + size - 1) = '\0';
			break;
		}
	}
	return size > 0 ? size : ret;
}