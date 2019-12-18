#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* statupd ) (TYPE_3__*) ;} ;
struct TYPE_9__ {TYPE_1__ func; } ;
typedef  TYPE_3__ ips_ha_t ;
struct TYPE_8__ {scalar_t__ command_id; } ;
struct TYPE_10__ {int value; TYPE_2__ fields; } ;
typedef  TYPE_4__ IPS_STATUS ;

/* Variables and functions */
 scalar_t__ IPS_MAX_CMDS ; 
 scalar_t__ TRUE ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int
ips_poll_for_flush_complete(ips_ha_t * ha)
{
	IPS_STATUS cstatus;

	while (TRUE) {
	    cstatus.value = (*ha->func.statupd) (ha);

	    if (cstatus.value == 0xffffffff)      /* If No Interrupt to process */
			break;

	    /* Success is when we see the Flush Command ID */
	    if (cstatus.fields.command_id == IPS_MAX_CMDS)
	        return 1;
	 }

	return 0;
}