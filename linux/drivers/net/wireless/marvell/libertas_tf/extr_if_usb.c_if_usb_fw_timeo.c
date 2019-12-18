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
struct timer_list {int dummy; } ;
struct if_usb_card {int /*<<< orphan*/  fw_wq; TYPE_1__* priv; int /*<<< orphan*/  fwdnldover; } ;
struct TYPE_2__ {int surpriseremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_USB ; 
 struct if_usb_card* cardp ; 
 struct if_usb_card* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_timeout ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_usb (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_fw_timeo(struct timer_list *t)
{
	struct if_usb_card *cardp = from_timer(cardp, t, fw_timeout);

	lbtf_deb_enter(LBTF_DEB_USB);
	if (!cardp->fwdnldover) {
		/* Download timed out */
		cardp->priv->surpriseremoved = 1;
		pr_err("Download timed out\n");
	} else {
		lbtf_deb_usb("Download complete, no event. Assuming success\n");
	}
	wake_up(&cardp->fw_wq);
	lbtf_deb_leave(LBTF_DEB_USB);
}