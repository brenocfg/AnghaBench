#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cs_hsi_iface {int /*<<< orphan*/  iface_state; TYPE_1__* cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int CS_STATE_CONFIGURED ; 
 int /*<<< orphan*/  CS_STATE_OPENED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cs_hsi_data_disable(struct cs_hsi_iface *hi, int old_state)
{
	if (old_state == CS_STATE_CONFIGURED) {
		dev_dbg(&hi->cl->device,
			"closing data channel with slot size 0\n");
		hi->iface_state = CS_STATE_OPENED;
	}
}