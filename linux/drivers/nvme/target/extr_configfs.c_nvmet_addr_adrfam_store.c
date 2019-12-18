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
struct TYPE_2__ {int /*<<< orphan*/  adrfam; } ;
struct nvmet_port {TYPE_1__ disc_addr; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  NVMF_ADDR_FAMILY_FC ; 
 int /*<<< orphan*/  NVMF_ADDR_FAMILY_IB ; 
 int /*<<< orphan*/  NVMF_ADDR_FAMILY_IP4 ; 
 int /*<<< orphan*/  NVMF_ADDR_FAMILY_IP6 ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_adrfam_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *port = to_nvmet_port(item);

	if (port->enabled) {
		pr_err("Cannot modify address while enabled\n");
		pr_err("Disable the address before modifying\n");
		return -EACCES;
	}

	if (sysfs_streq(page, "ipv4")) {
		port->disc_addr.adrfam = NVMF_ADDR_FAMILY_IP4;
	} else if (sysfs_streq(page, "ipv6")) {
		port->disc_addr.adrfam = NVMF_ADDR_FAMILY_IP6;
	} else if (sysfs_streq(page, "ib")) {
		port->disc_addr.adrfam = NVMF_ADDR_FAMILY_IB;
	} else if (sysfs_streq(page, "fc")) {
		port->disc_addr.adrfam = NVMF_ADDR_FAMILY_FC;
	} else {
		pr_err("Invalid value '%s' for adrfam\n", page);
		return -EINVAL;
	}

	return count;
}