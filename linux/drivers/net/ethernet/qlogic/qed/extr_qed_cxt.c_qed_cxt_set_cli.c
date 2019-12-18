#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ val; } ;
struct TYPE_3__ {scalar_t__ val; } ;
struct qed_ilt_client_cfg {int active; TYPE_2__ last; TYPE_1__ first; } ;

/* Variables and functions */

__attribute__((used)) static struct qed_ilt_client_cfg *qed_cxt_set_cli(struct qed_ilt_client_cfg
						  *p_cli)
{
	p_cli->active = false;
	p_cli->first.val = 0;
	p_cli->last.val = 0;
	return p_cli;
}