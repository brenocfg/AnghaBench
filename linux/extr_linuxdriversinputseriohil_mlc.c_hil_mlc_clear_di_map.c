#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* di_map; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */

__attribute__((used)) static void hil_mlc_clear_di_map(hil_mlc *mlc, int val)
{
	int j;

	for (j = val; j < 7 ; j++)
		mlc->di_map[j] = -1;
}