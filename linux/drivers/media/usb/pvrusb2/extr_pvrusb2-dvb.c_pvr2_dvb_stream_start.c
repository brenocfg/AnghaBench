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
struct pvr2_dvb_adapter {int dummy; } ;

/* Variables and functions */
 int pvr2_dvb_stream_do_start (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  pvr2_dvb_stream_end (struct pvr2_dvb_adapter*) ; 

__attribute__((used)) static int pvr2_dvb_stream_start(struct pvr2_dvb_adapter *adap)
{
	int ret = pvr2_dvb_stream_do_start(adap);
	if (ret < 0) pvr2_dvb_stream_end(adap);
	return ret;
}