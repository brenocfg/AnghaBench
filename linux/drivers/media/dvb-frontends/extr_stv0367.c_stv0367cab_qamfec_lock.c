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
typedef  int /*<<< orphan*/  u32 ;
struct stv0367_state {TYPE_1__* cab_state; } ;
struct TYPE_2__ {scalar_t__ qamfec_status_reg; } ;

/* Variables and functions */
 scalar_t__ F367CAB_QAMFEC_LOCK ; 
 int /*<<< orphan*/  stv0367_readbits (struct stv0367_state*,scalar_t__) ; 

__attribute__((used)) static u32 stv0367cab_qamfec_lock(struct stv0367_state *state)
{
	return stv0367_readbits(state,
		(state->cab_state->qamfec_status_reg ?
		 state->cab_state->qamfec_status_reg :
		 F367CAB_QAMFEC_LOCK));
}