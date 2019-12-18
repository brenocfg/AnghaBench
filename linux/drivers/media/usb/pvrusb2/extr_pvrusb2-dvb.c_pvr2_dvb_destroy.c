#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvr2_dvb_adapter {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  pvr2_channel_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_dvb_adapter_exit (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  pvr2_dvb_frontend_exit (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  pvr2_dvb_stream_end (struct pvr2_dvb_adapter*) ; 

__attribute__((used)) static void pvr2_dvb_destroy(struct pvr2_dvb_adapter *adap)
{
	pvr2_dvb_stream_end(adap);
	pvr2_dvb_frontend_exit(adap);
	pvr2_dvb_adapter_exit(adap);
	pvr2_channel_done(&adap->channel);
	kfree(adap);
}