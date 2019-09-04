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
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
#define  XGBE_AN_COMPLETE 133 
#define  XGBE_AN_ERROR 132 
#define  XGBE_AN_INCOMPAT_LINK 131 
#define  XGBE_AN_NO_LINK 130 
#define  XGBE_AN_PAGE_RECEIVED 129 
#define  XGBE_AN_READY 128 

__attribute__((used)) static const char *xgbe_state_as_string(enum xgbe_an state)
{
	switch (state) {
	case XGBE_AN_READY:
		return "Ready";
	case XGBE_AN_PAGE_RECEIVED:
		return "Page-Received";
	case XGBE_AN_INCOMPAT_LINK:
		return "Incompatible-Link";
	case XGBE_AN_COMPLETE:
		return "Complete";
	case XGBE_AN_NO_LINK:
		return "No-Link";
	case XGBE_AN_ERROR:
		return "Error";
	default:
		return "Undefined";
	}
}