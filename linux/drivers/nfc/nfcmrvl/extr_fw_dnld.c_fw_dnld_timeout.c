#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct nfcmrvl_private {TYPE_1__ fw_dnld; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  STATE_RESET ; 
 struct nfcmrvl_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_2__ fw_dnld ; 
 int /*<<< orphan*/  fw_dnld_over (struct nfcmrvl_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*) ; 
 struct nfcmrvl_private* priv ; 

__attribute__((used)) static void fw_dnld_timeout(struct timer_list *t)
{
	struct nfcmrvl_private *priv = from_timer(priv, t, fw_dnld.timer);

	nfc_err(priv->dev, "FW loading timeout");
	priv->fw_dnld.state = STATE_RESET;
	fw_dnld_over(priv, -ETIMEDOUT);
}