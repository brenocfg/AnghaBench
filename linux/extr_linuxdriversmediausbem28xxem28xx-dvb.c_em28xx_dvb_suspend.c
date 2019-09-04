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
struct em28xx_dvb {scalar_t__* fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_dvb; } ;
struct em28xx {TYPE_2__* intf; struct em28xx_dvb* dvb; TYPE_1__ board; scalar_t__ is_audio_only; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int dvb_frontend_suspend (scalar_t__) ; 

__attribute__((used)) static int em28xx_dvb_suspend(struct em28xx *dev)
{
	int ret = 0;

	if (dev->is_audio_only)
		return 0;

	if (!dev->board.has_dvb)
		return 0;

	dev_info(&dev->intf->dev, "Suspending DVB extension\n");
	if (dev->dvb) {
		struct em28xx_dvb *dvb = dev->dvb;

		if (dvb->fe[0]) {
			ret = dvb_frontend_suspend(dvb->fe[0]);
			dev_info(&dev->intf->dev, "fe0 suspend %d\n", ret);
		}
		if (dvb->fe[1]) {
			dvb_frontend_suspend(dvb->fe[1]);
			dev_info(&dev->intf->dev, "fe1 suspend %d\n", ret);
		}
	}

	return 0;
}