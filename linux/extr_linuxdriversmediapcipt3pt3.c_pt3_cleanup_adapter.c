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
struct pt3_board {struct pt3_adapter** adaps; } ;
struct dmx_demux {int /*<<< orphan*/  (* close ) (struct dmx_demux*) ;} ;
struct TYPE_4__ {struct dmx_demux dmx; } ;
struct pt3_adapter {int /*<<< orphan*/  dvb_adap; TYPE_2__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  i2c_demod; int /*<<< orphan*/  i2c_tuner; TYPE_1__* fe; scalar_t__ thread; } ;
struct TYPE_3__ {scalar_t__ frontend_priv; int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct pt3_adapter*) ; 
 int /*<<< orphan*/  one_adapter ; 
 int /*<<< orphan*/  pt3_free_dmabuf (struct pt3_adapter*) ; 
 int /*<<< orphan*/  pt3_stop_streaming (struct pt3_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct dmx_demux*) ; 

__attribute__((used)) static void pt3_cleanup_adapter(struct pt3_board *pt3, int index)
{
	struct pt3_adapter *adap;
	struct dmx_demux *dmx;

	adap = pt3->adaps[index];
	if (adap == NULL)
		return;

	/* stop demux kthread */
	if (adap->thread)
		pt3_stop_streaming(adap);

	dmx = &adap->demux.dmx;
	dmx->close(dmx);
	if (adap->fe) {
		adap->fe->callback = NULL;
		if (adap->fe->frontend_priv)
			dvb_unregister_frontend(adap->fe);
		dvb_module_release(adap->i2c_tuner);
		dvb_module_release(adap->i2c_demod);
	}
	pt3_free_dmabuf(adap);
	dvb_dmxdev_release(&adap->dmxdev);
	dvb_dmx_release(&adap->demux);
	if (index == 0 || !one_adapter)
		dvb_unregister_adapter(&adap->dvb_adap);
	kfree(adap);
	pt3->adaps[index] = NULL;
}