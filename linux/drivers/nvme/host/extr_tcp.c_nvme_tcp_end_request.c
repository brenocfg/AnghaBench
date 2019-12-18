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
typedef  union nvme_result {int dummy; } nvme_result ;
typedef  int u16 ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  nvme_end_request (struct request*,int /*<<< orphan*/ ,union nvme_result) ; 

__attribute__((used)) static inline void nvme_tcp_end_request(struct request *rq, u16 status)
{
	union nvme_result res = {};

	nvme_end_request(rq, cpu_to_le16(status << 1), res);
}