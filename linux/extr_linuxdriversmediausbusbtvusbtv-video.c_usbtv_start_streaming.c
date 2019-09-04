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
struct usbtv {int last_odd; scalar_t__ sequence; int /*<<< orphan*/ * udev; } ;

/* Variables and functions */
 int ENODEV ; 
 int usbtv_start (struct usbtv*) ; 
 struct usbtv* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int usbtv_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct usbtv *usbtv = vb2_get_drv_priv(vq);

	if (usbtv->udev == NULL)
		return -ENODEV;

	usbtv->last_odd = 1;
	usbtv->sequence = 0;
	return usbtv_start(usbtv);
}