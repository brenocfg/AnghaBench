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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVUTIL_DEVICE_DYING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvp_host_handshake_work ; 
 int /*<<< orphan*/  kvp_sendkey_work ; 
 int /*<<< orphan*/  kvp_timeout_work ; 
 TYPE_1__ kvp_transaction ; 

void hv_kvp_deinit(void)
{
	kvp_transaction.state = HVUTIL_DEVICE_DYING;
	cancel_delayed_work_sync(&kvp_host_handshake_work);
	cancel_delayed_work_sync(&kvp_timeout_work);
	cancel_work_sync(&kvp_sendkey_work);
	hvutil_transport_destroy(hvt);
}