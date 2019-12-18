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
struct bfa_fcs_lport_s {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
bfa_fcs_lport_clear_stats(struct bfa_fcs_lport_s *fcs_port)
{
	memset(&fcs_port->stats, 0, sizeof(struct bfa_lport_stats_s));
}