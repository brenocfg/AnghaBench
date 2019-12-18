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
typedef  scalar_t__ u32 ;
struct hfi1_pportdata {int linkinit_reason; } ;

/* Variables and functions */
 scalar_t__ HLS_UP_INIT ; 
#define  OPA_LINKINIT_INSUFIC_CAPABILITY 132 
#define  OPA_LINKINIT_OUTSIDE_POLICY 131 
#define  OPA_LINKINIT_QUARANTINED 130 
#define  OPA_LINKINIT_REASON_FLAPPING 129 
#define  OPA_LINKINIT_REASON_LINKUP 128 

__attribute__((used)) static const char *link_state_reason_name(struct hfi1_pportdata *ppd, u32 state)
{
	if (state == HLS_UP_INIT) {
		switch (ppd->linkinit_reason) {
		case OPA_LINKINIT_REASON_LINKUP:
			return "(LINKUP)";
		case OPA_LINKINIT_REASON_FLAPPING:
			return "(FLAPPING)";
		case OPA_LINKINIT_OUTSIDE_POLICY:
			return "(OUTSIDE_POLICY)";
		case OPA_LINKINIT_QUARANTINED:
			return "(QUARANTINED)";
		case OPA_LINKINIT_INSUFIC_CAPABILITY:
			return "(INSUFIC_CAPABILITY)";
		default:
			break;
		}
	}
	return "";
}