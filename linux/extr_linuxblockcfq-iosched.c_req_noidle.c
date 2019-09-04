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
struct request {int cmd_flags; } ;

/* Variables and functions */
 int REQ_IDLE ; 
 scalar_t__ REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 scalar_t__ req_op (struct request*) ; 

__attribute__((used)) static inline bool req_noidle(struct request *req)
{
	return req_op(req) == REQ_OP_WRITE &&
		(req->cmd_flags & (REQ_SYNC | REQ_IDLE)) == REQ_SYNC;
}