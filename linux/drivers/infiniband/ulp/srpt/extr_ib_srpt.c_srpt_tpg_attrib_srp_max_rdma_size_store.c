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
struct TYPE_2__ {unsigned long srp_max_rdma_size; } ;
struct srpt_port {TYPE_1__ port_attrib; } ;
struct se_portal_group {int dummy; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long DEFAULT_MAX_RDMA_SIZE ; 
 size_t EINVAL ; 
 unsigned long MAX_SRPT_RDMA_SIZE ; 
 struct se_portal_group* attrib_to_tpg (struct config_item*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,...) ; 
 struct srpt_port* srpt_tpg_to_sport (struct se_portal_group*) ; 

__attribute__((used)) static ssize_t srpt_tpg_attrib_srp_max_rdma_size_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_portal_group *se_tpg = attrib_to_tpg(item);
	struct srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	unsigned long val;
	int ret;

	ret = kstrtoul(page, 0, &val);
	if (ret < 0) {
		pr_err("kstrtoul() failed with ret: %d\n", ret);
		return -EINVAL;
	}
	if (val > MAX_SRPT_RDMA_SIZE) {
		pr_err("val: %lu exceeds MAX_SRPT_RDMA_SIZE: %d\n", val,
			MAX_SRPT_RDMA_SIZE);
		return -EINVAL;
	}
	if (val < DEFAULT_MAX_RDMA_SIZE) {
		pr_err("val: %lu smaller than DEFAULT_MAX_RDMA_SIZE: %d\n",
			val, DEFAULT_MAX_RDMA_SIZE);
		return -EINVAL;
	}
	sport->port_attrib.srp_max_rdma_size = val;

	return count;
}