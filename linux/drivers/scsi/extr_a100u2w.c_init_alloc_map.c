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
typedef  int u8 ;
struct orc_host {int** allocation_map; } ;

/* Variables and functions */
 int MAX_CHANNELS ; 

__attribute__((used)) static void init_alloc_map(struct orc_host * host)
{
	u8 i, j;

	for (i = 0; i < MAX_CHANNELS; i++) {
		for (j = 0; j < 8; j++) {
			host->allocation_map[i][j] = 0xffffffff;
		}
	}
}