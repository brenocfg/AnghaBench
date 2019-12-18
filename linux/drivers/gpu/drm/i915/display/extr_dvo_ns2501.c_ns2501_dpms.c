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
struct ns2501_priv {TYPE_1__* conf; } ;
struct intel_dvo_device {scalar_t__ dev_priv; } ;
struct TYPE_2__ {int sync; int syncb; int conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int NS2501_34_ENABLE_BACKLIGHT ; 
 int NS2501_34_ENABLE_OUTPUT ; 
 int NS2501_8_BPAS ; 
 int NS2501_8_HEN ; 
 int NS2501_8_VEN ; 
 int /*<<< orphan*/  NS2501_REG34 ; 
 int /*<<< orphan*/  NS2501_REG41 ; 
 int /*<<< orphan*/  NS2501_REG8 ; 
 int /*<<< orphan*/  NS2501_REGC0 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ns2501_writeb (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ns2501_dpms(struct intel_dvo_device *dvo, bool enable)
{
	struct ns2501_priv *ns = (struct ns2501_priv *)(dvo->dev_priv);

	DRM_DEBUG_KMS("Trying set the dpms of the DVO to %i\n", enable);

	if (enable) {
		ns2501_writeb(dvo, NS2501_REGC0, ns->conf->sync | 0x08);

		ns2501_writeb(dvo, NS2501_REG41, ns->conf->syncb);

		ns2501_writeb(dvo, NS2501_REG34, NS2501_34_ENABLE_OUTPUT);
		msleep(15);

		ns2501_writeb(dvo, NS2501_REG8,
				ns->conf->conf | NS2501_8_BPAS);
		if (!(ns->conf->conf & NS2501_8_BPAS))
			ns2501_writeb(dvo, NS2501_REG8, ns->conf->conf);
		msleep(200);

		ns2501_writeb(dvo, NS2501_REG34,
			NS2501_34_ENABLE_OUTPUT | NS2501_34_ENABLE_BACKLIGHT);

		ns2501_writeb(dvo, NS2501_REGC0, ns->conf->sync);
	} else {
		ns2501_writeb(dvo, NS2501_REG34, NS2501_34_ENABLE_OUTPUT);
		msleep(200);

		ns2501_writeb(dvo, NS2501_REG8, NS2501_8_VEN | NS2501_8_HEN |
				NS2501_8_BPAS);
		msleep(15);

		ns2501_writeb(dvo, NS2501_REG34, 0x00);
	}
}