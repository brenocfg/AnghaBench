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
struct urb {scalar_t__ status; int /*<<< orphan*/  actual_length; TYPE_1__* dev; scalar_t__ context; } ;
struct lbs_private {scalar_t__ dnld_sent; } ;
struct if_usb_card {struct lbs_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DNLD_BOOTCMD_SENT ; 
 int /*<<< orphan*/  lbs_deb_usb2 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lbs_host_to_card_done (struct lbs_private*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 

__attribute__((used)) static void if_usb_write_bulk_callback(struct urb *urb)
{
	struct if_usb_card *cardp = (struct if_usb_card *) urb->context;

	/* handle the transmission complete validations */

	if (urb->status == 0) {
		struct lbs_private *priv = cardp->priv;

		lbs_deb_usb2(&urb->dev->dev, "URB status is successful\n");
		lbs_deb_usb2(&urb->dev->dev, "Actual length transmitted %d\n",
			     urb->actual_length);

		/* Boot commands such as UPDATE_FW and UPDATE_BOOT2 are not
		 * passed up to the lbs level.
		 */
		if (priv && priv->dnld_sent != DNLD_BOOTCMD_SENT)
			lbs_host_to_card_done(priv);
	} else {
		/* print the failure status number for debug */
		pr_info("URB in failure status: %d\n", urb->status);
	}
}