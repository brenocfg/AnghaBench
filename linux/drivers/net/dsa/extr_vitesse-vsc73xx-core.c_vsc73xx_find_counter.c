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
typedef  scalar_t__ u8 ;
struct vsc73xx_counter {scalar_t__ counter; } ;
struct vsc73xx {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vsc73xx_counter*) ; 
 struct vsc73xx_counter* vsc73xx_rx_counters ; 
 struct vsc73xx_counter* vsc73xx_tx_counters ; 

__attribute__((used)) static const struct vsc73xx_counter *
vsc73xx_find_counter(struct vsc73xx *vsc,
		     u8 counter,
		     bool tx)
{
	const struct vsc73xx_counter *cnts;
	int num_cnts;
	int i;

	if (tx) {
		cnts = vsc73xx_tx_counters;
		num_cnts = ARRAY_SIZE(vsc73xx_tx_counters);
	} else {
		cnts = vsc73xx_rx_counters;
		num_cnts = ARRAY_SIZE(vsc73xx_rx_counters);
	}

	for (i = 0; i < num_cnts; i++) {
		const struct vsc73xx_counter *cnt;

		cnt = &cnts[i];
		if (cnt->counter == counter)
			return cnt;
	}

	return NULL;
}