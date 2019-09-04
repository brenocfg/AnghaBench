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
typedef  int /*<<< orphan*/  u32 ;
struct stv0367_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_FSM_STATUS ; 
 int /*<<< orphan*/  stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0367cab_fsm_status(struct stv0367_state *state)
{
	return stv0367_readbits(state, F367CAB_FSM_STATUS);
}