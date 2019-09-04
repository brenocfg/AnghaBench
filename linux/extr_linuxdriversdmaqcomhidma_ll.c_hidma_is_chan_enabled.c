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
#define  HIDMA_CH_ENABLED 129 
#define  HIDMA_CH_RUNNING 128 

__attribute__((used)) static int hidma_is_chan_enabled(int state)
{
	switch (state) {
	case HIDMA_CH_ENABLED:
	case HIDMA_CH_RUNNING:
		return true;
	default:
		return false;
	}
}