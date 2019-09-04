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
struct dvb_net {int exit; int /*<<< orphan*/ * state; TYPE_1__* dvbdev; } ;
struct TYPE_2__ {int users; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int DVB_NET_DEVICES_MAX ; 
 int /*<<< orphan*/  dvb_net_remove_if (struct dvb_net*,int) ; 
 int /*<<< orphan*/  dvb_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void dvb_net_release (struct dvb_net *dvbnet)
{
	int i;

	dvbnet->exit = 1;
	if (dvbnet->dvbdev->users < 1)
		wait_event(dvbnet->dvbdev->wait_queue,
				dvbnet->dvbdev->users==1);

	dvb_unregister_device(dvbnet->dvbdev);

	for (i=0; i<DVB_NET_DEVICES_MAX; i++) {
		if (!dvbnet->state[i])
			continue;
		dvb_net_remove_if(dvbnet, i);
	}
}