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
typedef  scalar_t__ u8 ;
struct be_mcc_compl {scalar_t__ flags; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASYNC_EVENT_PORT_MISCONFIG ; 
 scalar_t__ ASYNC_EVENT_TYPE_MASK ; 
 scalar_t__ ASYNC_EVENT_TYPE_SHIFT ; 
 int /*<<< orphan*/  be_async_port_misconfig_event_process (struct be_adapter*,struct be_mcc_compl*) ; 

__attribute__((used)) static void be_async_sliport_evt_process(struct be_adapter *adapter,
					 struct be_mcc_compl *cmp)
{
	u8 event_type = (cmp->flags >> ASYNC_EVENT_TYPE_SHIFT) &
			ASYNC_EVENT_TYPE_MASK;

	if (event_type == ASYNC_EVENT_PORT_MISCONFIG)
		be_async_port_misconfig_event_process(adapter, cmp);
}