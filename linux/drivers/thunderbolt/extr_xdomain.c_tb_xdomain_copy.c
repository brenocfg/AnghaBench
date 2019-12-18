#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ err; } ;
struct tb_cfg_request {TYPE_1__ result; int /*<<< orphan*/  response_size; int /*<<< orphan*/  response; } ;
struct ctl_pkg {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tb_xdomain_copy(struct tb_cfg_request *req,
			    const struct ctl_pkg *pkg)
{
	memcpy(req->response, pkg->buffer, req->response_size);
	req->result.err = 0;
	return true;
}