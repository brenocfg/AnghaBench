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
struct nvmet_tcp_queue {int dummy; } ;

/* Variables and functions */
 int nvmet_tcp_try_recv_one (struct nvmet_tcp_queue*) ; 

__attribute__((used)) static int nvmet_tcp_try_recv(struct nvmet_tcp_queue *queue,
		int budget, int *recvs)
{
	int i, ret = 0;

	for (i = 0; i < budget; i++) {
		ret = nvmet_tcp_try_recv_one(queue);
		if (ret <= 0)
			break;
		(*recvs)++;
	}

	return ret;
}