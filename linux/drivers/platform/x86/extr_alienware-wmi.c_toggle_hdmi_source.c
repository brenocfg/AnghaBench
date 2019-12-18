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
struct wmax_basic_args {int arg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMAX_METHOD_HDMI_SOURCE ; 
 int /*<<< orphan*/  alienware_wmax_command (struct wmax_basic_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static ssize_t toggle_hdmi_source(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	acpi_status status;
	struct wmax_basic_args args;
	if (strcmp(buf, "gpu\n") == 0)
		args.arg = 1;
	else if (strcmp(buf, "input\n") == 0)
		args.arg = 2;
	else
		args.arg = 3;
	pr_debug("alienware-wmi: setting hdmi to %d : %s", args.arg, buf);

	status = alienware_wmax_command(&args, WMAX_METHOD_HDMI_SOURCE, NULL);

	if (ACPI_FAILURE(status))
		pr_err("alienware-wmi: HDMI toggle failed: results: %u\n",
		       status);
	return count;
}