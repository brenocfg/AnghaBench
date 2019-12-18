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
struct pvr2_hdw {unsigned long freqValTelevision; unsigned long freqValRadio; scalar_t__ freqSelector; } ;

/* Variables and functions */

unsigned long pvr2_hdw_get_cur_freq(struct pvr2_hdw *hdw)
{
	return hdw->freqSelector ? hdw->freqValTelevision : hdw->freqValRadio;
}