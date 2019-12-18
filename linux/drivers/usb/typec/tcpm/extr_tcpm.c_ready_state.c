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
struct tcpm_port {scalar_t__ pwr_role; } ;
typedef  enum tcpm_state { ____Placeholder_tcpm_state } tcpm_state ;

/* Variables and functions */
 int SNK_READY ; 
 int SRC_READY ; 
 scalar_t__ TYPEC_SOURCE ; 

__attribute__((used)) static inline enum tcpm_state ready_state(struct tcpm_port *port)
{
	if (port->pwr_role == TYPEC_SOURCE)
		return SRC_READY;
	else
		return SNK_READY;
}