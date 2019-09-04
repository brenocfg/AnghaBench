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
struct TYPE_2__ {int channels; } ;
typedef  TYPE_1__ diva_maint_client_t ;

/* Variables and functions */

int SuperTraceGetNumberOfChannels(void *AdapterHandle) {
	if (AdapterHandle) {
		diva_maint_client_t *pC = (diva_maint_client_t *)AdapterHandle;

		return (pC->channels);
	}

	return (0);
}