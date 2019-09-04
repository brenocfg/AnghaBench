#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
struct TYPE_5__ {scalar_t__* ch_flow_plci; scalar_t__* ch_flow_control; } ;
struct TYPE_4__ {scalar_t__ Id; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int MAX_NL_CHANNEL ; 

__attribute__((used)) static void channel_flow_control_remove(PLCI *plci) {
	DIVA_CAPI_ADAPTER *a = plci->adapter;
	word i;
	for (i = 1; i < MAX_NL_CHANNEL + 1; i++) {
		if (a->ch_flow_plci[i] == plci->Id) {
			a->ch_flow_plci[i] = 0;
			a->ch_flow_control[i] = 0;
		}
	}
}