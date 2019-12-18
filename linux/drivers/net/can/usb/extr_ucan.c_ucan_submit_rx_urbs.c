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
struct urb {int dummy; } ;
struct ucan_priv {int /*<<< orphan*/  rx_urbs; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UCAN_MAX_RX_URBS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ucan_cleanup_rx_urbs (struct ucan_priv*,struct urb**) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucan_submit_rx_urbs(struct ucan_priv *up, struct urb **urbs)
{
	int i, ret;

	/* Iterate over all urbs to submit. On success remove the urb
	 * from the list.
	 */
	for (i = 0; i < UCAN_MAX_RX_URBS; i++) {
		ret = usb_submit_urb(urbs[i], GFP_KERNEL);
		if (ret) {
			netdev_err(up->netdev,
				   "could not submit urb; code: %d\n",
				   ret);
			goto err;
		}

		/* Anchor URB and drop reference, USB core will take
		 * care of freeing it
		 */
		usb_free_urb(urbs[i]);
		urbs[i] = NULL;
	}
	return 0;

err:
	/* Cleanup unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);

	/* Kill urbs that are already submitted */
	usb_kill_anchored_urbs(&up->rx_urbs);

	return ret;
}