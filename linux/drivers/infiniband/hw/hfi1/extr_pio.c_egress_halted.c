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
typedef  int u64 ;

/* Variables and functions */
 int SEND_EGRESS_CTXT_STATUS_CTXT_EGRESS_HALT_STATUS_SMASK ; 

__attribute__((used)) static bool egress_halted(u64 reg)
{
	return !!(reg & SEND_EGRESS_CTXT_STATUS_CTXT_EGRESS_HALT_STATUS_SMASK);
}