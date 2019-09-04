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
struct camera_data {TYPE_1__* sbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int NUM_SBUF ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_sbufs(struct camera_data *cam)
{
	int i;

	for (i = 0; i < NUM_SBUF; i++) {
		if(cam->sbuf[i].urb) {
			usb_kill_urb(cam->sbuf[i].urb);
			usb_free_urb(cam->sbuf[i].urb);
			cam->sbuf[i].urb = NULL;
		}
		if(cam->sbuf[i].data) {
			kfree(cam->sbuf[i].data);
			cam->sbuf[i].data = NULL;
		}
	}
}