#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union bfa_port_stats_u {int dummy; } bfa_port_stats_u ;
struct TYPE_6__ {int /*<<< orphan*/  kva; } ;
struct bfa_port_s {int /*<<< orphan*/  (* stats_cbfn ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  stats_cbarg; scalar_t__ stats_reset_time; TYPE_3__* stats; TYPE_2__ stats_dma; int /*<<< orphan*/  stats_busy; scalar_t__ stats_status; } ;
typedef  scalar_t__ bfa_status_t ;
struct TYPE_5__ {scalar_t__ secs_reset; } ;
struct TYPE_7__ {TYPE_1__ fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_port_stats_swap (struct bfa_port_s*,TYPE_3__*) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bfa_port_get_stats_isr(struct bfa_port_s *port, bfa_status_t status)
{
	port->stats_status = status;
	port->stats_busy = BFA_FALSE;

	if (status == BFA_STATUS_OK) {
		memcpy(port->stats, port->stats_dma.kva,
		       sizeof(union bfa_port_stats_u));
		bfa_port_stats_swap(port, port->stats);

		port->stats->fc.secs_reset = ktime_get_seconds() - port->stats_reset_time;
	}

	if (port->stats_cbfn) {
		port->stats_cbfn(port->stats_cbarg, status);
		port->stats_cbfn = NULL;
	}
}