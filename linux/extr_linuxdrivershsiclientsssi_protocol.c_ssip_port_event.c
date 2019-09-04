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
struct hsi_client {int dummy; } ;

/* Variables and functions */
#define  HSI_EVENT_START_RX 129 
#define  HSI_EVENT_STOP_RX 128 
 int /*<<< orphan*/  ssip_start_rx (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_stop_rx (struct hsi_client*) ; 

__attribute__((used)) static void ssip_port_event(struct hsi_client *cl, unsigned long event)
{
	switch (event) {
	case HSI_EVENT_START_RX:
		ssip_start_rx(cl);
		break;
	case HSI_EVENT_STOP_RX:
		ssip_stop_rx(cl);
		break;
	default:
		return;
	}
}