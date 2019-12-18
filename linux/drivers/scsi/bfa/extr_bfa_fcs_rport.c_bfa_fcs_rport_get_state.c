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
struct bfa_fcs_rport_s {int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rport_sm_table ; 

int
bfa_fcs_rport_get_state(struct bfa_fcs_rport_s *rport)
{
	return bfa_sm_to_state(rport_sm_table, rport->sm);
}