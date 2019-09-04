#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int error; int /*<<< orphan*/  proc_id; } ;
struct TYPE_5__ {TYPE_1__ rsp; } ;
struct TYPE_6__ {TYPE_2__ context; } ;
struct as10x_cmd_t {TYPE_3__ body; } ;

/* Variables and functions */
 int AS10X_CMD_ERROR ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

int as10x_context_rsp_parse(struct as10x_cmd_t *prsp, uint16_t proc_id)
{
	int err;

	err = prsp->body.context.rsp.error;

	if ((err == 0) &&
	    (le16_to_cpu(prsp->body.context.rsp.proc_id) == proc_id)) {
		return 0;
	}
	return AS10X_CMD_ERROR;
}