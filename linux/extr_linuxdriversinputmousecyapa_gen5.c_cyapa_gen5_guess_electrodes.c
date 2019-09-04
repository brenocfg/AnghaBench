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
struct cyapa {int electrodes_rx; int electrodes_x; int electrodes_y; } ;

/* Variables and functions */
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void cyapa_gen5_guess_electrodes(struct cyapa *cyapa,
		int *electrodes_rx, int *electrodes_tx)
{
	if (cyapa->electrodes_rx != 0) {
		*electrodes_rx = cyapa->electrodes_rx;
		*electrodes_tx = (cyapa->electrodes_x == *electrodes_rx) ?
				cyapa->electrodes_y : cyapa->electrodes_x;
	} else {
		*electrodes_tx = min(cyapa->electrodes_x, cyapa->electrodes_y);
		*electrodes_rx = max(cyapa->electrodes_x, cyapa->electrodes_y);
	}
}