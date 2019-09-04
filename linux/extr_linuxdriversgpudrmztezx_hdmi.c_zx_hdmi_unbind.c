#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct zx_hdmi {scalar_t__ audio_pdev; TYPE_3__ encoder; TYPE_4__ connector; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;

/* Variables and functions */
 struct zx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void zx_hdmi_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct zx_hdmi *hdmi = dev_get_drvdata(dev);

	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);

	if (hdmi->audio_pdev)
		platform_device_unregister(hdmi->audio_pdev);
}