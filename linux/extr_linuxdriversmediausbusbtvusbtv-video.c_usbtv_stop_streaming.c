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
struct vb2_queue {int dummy; } ;
struct usbtv {scalar_t__ udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbtv_stop (struct usbtv*) ; 
 struct usbtv* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void usbtv_stop_streaming(struct vb2_queue *vq)
{
	struct usbtv *usbtv = vb2_get_drv_priv(vq);

	if (usbtv->udev)
		usbtv_stop(usbtv);
}