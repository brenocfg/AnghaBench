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
typedef  enum zpci_state { ____Placeholder_zpci_state } zpci_state ;

/* Variables and functions */
 int ZPCI_FN_STATE_CONFIGURED ; 
 int ZPCI_FN_STATE_ONLINE ; 

__attribute__((used)) static int zpci_fn_configured(enum zpci_state state)
{
	return state == ZPCI_FN_STATE_CONFIGURED ||
	       state == ZPCI_FN_STATE_ONLINE;
}