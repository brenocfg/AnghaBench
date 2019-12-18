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
typedef  int u8 ;
struct TYPE_2__ {int treq; } ;
struct nvmet_port {TYPE_1__ disc_addr; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EINVAL ; 
 int NVME_TREQ_SECURE_CHANNEL_MASK ; 
 int NVMF_TREQ_NOT_REQUIRED ; 
 int NVMF_TREQ_NOT_SPECIFIED ; 
 int NVMF_TREQ_REQUIRED ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_treq_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);
	u8 treq = port->disc_addr.treq & ~NVME_TREQ_SECURE_CHANNEL_MASK;

	if (port->enabled) {
		pr_err("Cannot modify address while enabled\n");
		pr_err("Disable the address before modifying\n");
		return -EACCES;
	}

	if (sysfs_streq(page, "not specified")) {
		treq |= NVMF_TREQ_NOT_SPECIFIED;
	} else if (sysfs_streq(page, "required")) {
		treq |= NVMF_TREQ_REQUIRED;
	} else if (sysfs_streq(page, "not required")) {
		treq |= NVMF_TREQ_NOT_REQUIRED;
	} else {
		pr_err("Invalid value '%s' for treq\n", page);
		return -EINVAL;
	}
	port->disc_addr.treq = treq;

	return count;
}