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
struct rsi_hw {int ps_state; } ;
typedef  enum ps_state { ____Placeholder_ps_state } ps_state ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ZONE ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_psstate (int) ; 

__attribute__((used)) static inline void rsi_modify_ps_state(struct rsi_hw *adapter,
				       enum ps_state nstate)
{
	rsi_dbg(INFO_ZONE, "PS state changed %s => %s\n",
		str_psstate(adapter->ps_state),
		str_psstate(nstate));

	adapter->ps_state = nstate;
}