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
struct fcloop_tport {int dummy; } ;
struct fcloop_nport {struct fcloop_tport* tport; TYPE_1__* rport; } ;
struct TYPE_2__ {int /*<<< orphan*/ * targetport; } ;

/* Variables and functions */

__attribute__((used)) static struct fcloop_tport *
__unlink_target_port(struct fcloop_nport *nport)
{
	struct fcloop_tport *tport = nport->tport;

	if (tport && nport->rport)
		nport->rport->targetport = NULL;
	nport->tport = NULL;

	return tport;
}