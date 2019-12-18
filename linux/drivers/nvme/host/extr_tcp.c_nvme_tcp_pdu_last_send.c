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
struct nvme_tcp_request {int dummy; } ;

/* Variables and functions */
 int nvme_tcp_pdu_data_left (struct nvme_tcp_request*) ; 

__attribute__((used)) static inline size_t nvme_tcp_pdu_last_send(struct nvme_tcp_request *req,
		int len)
{
	return nvme_tcp_pdu_data_left(req) <= len;
}