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
struct nvmet_port {int /*<<< orphan*/  inline_data_size; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EINVAL ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_param_inline_data_size_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);
	int ret;

	if (port->enabled) {
		pr_err("Cannot modify inline_data_size while port enabled\n");
		pr_err("Disable the port before modifying\n");
		return -EACCES;
	}
	ret = kstrtoint(page, 0, &port->inline_data_size);
	if (ret) {
		pr_err("Invalid value '%s' for inline_data_size\n", page);
		return -EINVAL;
	}
	return count;
}