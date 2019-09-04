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
typedef  int u8 ;
struct cm_req_msg {int /*<<< orphan*/  offset32; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void cm_req_set_resp_res(struct cm_req_msg *req_msg, u8 resp_res)
{
	req_msg->offset32 = cpu_to_be32(resp_res |
					(be32_to_cpu(req_msg->offset32) &
					 0xFFFFFF00));
}