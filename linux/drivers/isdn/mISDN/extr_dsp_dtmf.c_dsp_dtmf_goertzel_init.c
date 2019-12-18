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
struct TYPE_2__ {char lastwhat; char lastdigit; scalar_t__ count; scalar_t__ size; } ;
struct dsp {TYPE_1__ dtmf; } ;

/* Variables and functions */

void dsp_dtmf_goertzel_init(struct dsp *dsp)
{
	dsp->dtmf.size = 0;
	dsp->dtmf.lastwhat = '\0';
	dsp->dtmf.lastdigit = '\0';
	dsp->dtmf.count = 0;
}