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
typedef  int u64 ;
struct sockaddr_ib {int /*<<< orphan*/  sib_sid; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_cm_id {scalar_t__ ps; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_port (struct sockaddr*) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 

__be64 rdma_get_service_id(struct rdma_cm_id *id, struct sockaddr *addr)
{
	if (addr->sa_family == AF_IB)
		return ((struct sockaddr_ib *) addr)->sib_sid;

	return cpu_to_be64(((u64)id->ps << 16) + be16_to_cpu(cma_port(addr)));
}