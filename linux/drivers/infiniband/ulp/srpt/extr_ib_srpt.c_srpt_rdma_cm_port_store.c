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
typedef  scalar_t__ u16 ;
struct sockaddr_in6 {void* sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct rdma_cm_id {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int PTR_ERR (struct rdma_cm_id*) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 int kstrtou16 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_cm_id ; 
 int /*<<< orphan*/  rdma_cm_mutex ; 
 scalar_t__ rdma_cm_port ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 struct rdma_cm_id* srpt_create_rdma_id (struct sockaddr*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct rdma_cm_id*) ; 

__attribute__((used)) static ssize_t srpt_rdma_cm_port_store(struct config_item *item,
				       const char *page, size_t count)
{
	struct sockaddr_in  addr4 = { .sin_family  = AF_INET  };
	struct sockaddr_in6 addr6 = { .sin6_family = AF_INET6 };
	struct rdma_cm_id *new_id = NULL;
	u16 val;
	int ret;

	ret = kstrtou16(page, 0, &val);
	if (ret < 0)
		return ret;
	ret = count;
	if (rdma_cm_port == val)
		goto out;

	if (val) {
		addr6.sin6_port = cpu_to_be16(val);
		new_id = srpt_create_rdma_id((struct sockaddr *)&addr6);
		if (IS_ERR(new_id)) {
			addr4.sin_port = cpu_to_be16(val);
			new_id = srpt_create_rdma_id((struct sockaddr *)&addr4);
			if (IS_ERR(new_id)) {
				ret = PTR_ERR(new_id);
				goto out;
			}
		}
	}

	mutex_lock(&rdma_cm_mutex);
	rdma_cm_port = val;
	swap(rdma_cm_id, new_id);
	mutex_unlock(&rdma_cm_mutex);

	if (new_id)
		rdma_destroy_id(new_id);
	ret = count;
out:
	return ret;
}