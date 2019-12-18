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
struct bus_id_priv {TYPE_1__* sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ud; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_EVENT_REMOVED ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_stop_eh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown_busid(struct bus_id_priv *busid_priv)
{
	usbip_event_add(&busid_priv->sdev->ud, SDEV_EVENT_REMOVED);

	/* wait for the stop of the event handler */
	usbip_stop_eh(&busid_priv->sdev->ud);
}