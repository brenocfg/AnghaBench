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
struct nvmet_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_execute_abort(struct nvmet_req *req)
{
	nvmet_set_result(req, 1);
	nvmet_req_complete(req, 0);
}