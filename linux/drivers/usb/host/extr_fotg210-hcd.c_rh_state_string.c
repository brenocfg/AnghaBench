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
struct fotg210_hcd {int rh_state; } ;

/* Variables and functions */
#define  FOTG210_RH_HALTED 131 
#define  FOTG210_RH_RUNNING 130 
#define  FOTG210_RH_STOPPING 129 
#define  FOTG210_RH_SUSPENDED 128 

__attribute__((used)) static const char *rh_state_string(struct fotg210_hcd *fotg210)
{
	switch (fotg210->rh_state) {
	case FOTG210_RH_HALTED:
		return "halted";
	case FOTG210_RH_SUSPENDED:
		return "suspended";
	case FOTG210_RH_RUNNING:
		return "running";
	case FOTG210_RH_STOPPING:
		return "stopping";
	}
	return "?";
}