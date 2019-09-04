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

/* Variables and functions */
 int /*<<< orphan*/  dsp_hwec ; 
 int /*<<< orphan*/  mISDN_dsp_element_unregister (int /*<<< orphan*/ ) ; 

void dsp_hwec_exit(void)
{
	mISDN_dsp_element_unregister(dsp_hwec);
}