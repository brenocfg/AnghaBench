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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {int dummy; } ;
struct dummy_hcd {int stream_en_ep; TYPE_1__* dum; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int dummy_get_ep_idx (int /*<<< orphan*/ *) ; 
 struct dummy_hcd* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_max_streams_for_pipe (struct dummy_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_endpoint_num (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_free_streams(struct usb_hcd *hcd, struct usb_device *udev,
	struct usb_host_endpoint **eps, unsigned int num_eps,
	gfp_t mem_flags)
{
	struct dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);
	unsigned long flags;
	int ret;
	unsigned int index;
	unsigned int i;

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	for (i = 0; i < num_eps; i++) {
		index = dummy_get_ep_idx(&eps[i]->desc);
		if (!((1 << index) & dum_hcd->stream_en_ep)) {
			ret = -EINVAL;
			goto out;
		}
	}

	for (i = 0; i < num_eps; i++) {
		index = dummy_get_ep_idx(&eps[i]->desc);
		dum_hcd->stream_en_ep &= ~(1 << index);
		set_max_streams_for_pipe(dum_hcd,
				usb_endpoint_num(&eps[i]->desc), 0);
	}
	ret = 0;
out:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	return ret;
}