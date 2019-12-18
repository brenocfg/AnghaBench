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
struct TYPE_3__ {int /*<<< orphan*/  num; int /*<<< orphan*/  device; } ;
struct pt3_adapter {int /*<<< orphan*/ * thread; TYPE_2__* fe; TYPE_1__ dvb_adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kthread_stop (int /*<<< orphan*/ *) ; 
 int pt3_stop_dma (struct pt3_adapter*) ; 

__attribute__((used)) static int pt3_stop_streaming(struct pt3_adapter *adap)
{
	int ret;

	ret = pt3_stop_dma(adap);
	if (ret)
		dev_warn(adap->dvb_adap.device,
			 "PT3: failed to stop streaming of adap:%d/FE:%d\n",
			 adap->dvb_adap.num, adap->fe->id);

	/* kill the fetching thread */
	ret = kthread_stop(adap->thread);
	adap->thread = NULL;
	return ret;
}