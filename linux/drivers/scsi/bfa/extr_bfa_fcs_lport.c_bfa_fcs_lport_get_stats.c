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
struct bfa_lport_stats_s {int dummy; } ;
struct bfa_fcs_lport_s {struct bfa_lport_stats_s stats; } ;

/* Variables and functions */

void
bfa_fcs_lport_get_stats(struct bfa_fcs_lport_s *fcs_port,
	 struct bfa_lport_stats_s *port_stats)
{
	*port_stats = fcs_port->stats;
}