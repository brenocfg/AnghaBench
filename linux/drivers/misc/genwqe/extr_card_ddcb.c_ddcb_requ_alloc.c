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
struct genwqe_ddcb_cmd {int dummy; } ;
struct ddcb_requ {struct genwqe_ddcb_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ddcb_requ* kzalloc (int,int /*<<< orphan*/ ) ; 

struct genwqe_ddcb_cmd *ddcb_requ_alloc(void)
{
	struct ddcb_requ *req;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return NULL;

	return &req->cmd;
}