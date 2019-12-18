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
struct rvu {int dummy; } ;
struct ready_msg_rsp {int dummy; } ;
struct msg_req {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rvu_mbox_handler_ready(struct rvu *rvu, struct msg_req *req,
				  struct ready_msg_rsp *rsp)
{
	return 0;
}