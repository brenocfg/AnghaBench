#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dvbdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  num; int /*<<< orphan*/  device; } ;
struct pt3_adapter {struct task_struct* thread; TYPE_3__ dmxdev; TYPE_1__ dvb_adap; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct pt3_adapter*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt3_fetch_thread ; 
 int pt3_start_dma (struct pt3_adapter*) ; 

__attribute__((used)) static int pt3_start_streaming(struct pt3_adapter *adap)
{
	struct task_struct *thread;

	/* start fetching thread */
	thread = kthread_run(pt3_fetch_thread, adap, "pt3-ad%i-dmx%i",
				adap->dvb_adap.num, adap->dmxdev.dvbdev->id);
	if (IS_ERR(thread)) {
		int ret = PTR_ERR(thread);

		adap->thread = NULL;
		dev_warn(adap->dvb_adap.device,
			 "PT3 (adap:%d, dmx:%d): failed to start kthread\n",
			 adap->dvb_adap.num, adap->dmxdev.dvbdev->id);
		return ret;
	}
	adap->thread = thread;

	return pt3_start_dma(adap);
}