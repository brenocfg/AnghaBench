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
typedef  scalar_t__ u16 ;
struct nvkm_perfdom {int signal_nr; TYPE_1__* signal; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */

__attribute__((used)) static u16
nvkm_perfdom_count_perfsig(struct nvkm_perfdom *dom)
{
	u16 signal_nr = 0;
	int i;

	if (dom) {
		for (i = 0; i < dom->signal_nr; i++) {
			if (dom->signal[i].name)
				signal_nr++;
		}
	}
	return signal_nr;
}