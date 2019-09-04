#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ddi; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int /*<<< orphan*/  hil_mlc_clear_di_map (TYPE_1__*,int) ; 

__attribute__((used)) static int hilse_dec_ddi(hil_mlc *mlc, int unused)
{
	mlc->ddi--;
	if (mlc->ddi <= -1) {
		mlc->ddi = -1;
		hil_mlc_clear_di_map(mlc, 0);
		return -1;
	}
	hil_mlc_clear_di_map(mlc, mlc->ddi + 1);

	return 0;
}