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
typedef  int u8 ;
struct opa_port_states {int portphysstate_portstate; } ;

/* Variables and functions */
 int OPA_PI_MASK_PORT_STATE ; 

__attribute__((used)) static inline u8 port_states_to_logical_state(struct opa_port_states *ps)
{
	return ps->portphysstate_portstate & OPA_PI_MASK_PORT_STATE;
}