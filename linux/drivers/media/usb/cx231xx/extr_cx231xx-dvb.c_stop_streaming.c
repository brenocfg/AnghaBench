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
struct TYPE_2__ {struct cx231xx* priv; } ;
struct cx231xx_dvb {TYPE_1__ adapter; } ;
struct cx231xx {scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_SUSPEND ; 
 int /*<<< orphan*/  cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_uninit_bulk (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_isoc (struct cx231xx*) ; 

__attribute__((used)) static int stop_streaming(struct cx231xx_dvb *dvb)
{
	struct cx231xx *dev = dvb->adapter.priv;

	if (dev->USE_ISO)
		cx231xx_uninit_isoc(dev);
	else
		cx231xx_uninit_bulk(dev);

	cx231xx_set_mode(dev, CX231XX_SUSPEND);

	return 0;
}