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
struct TYPE_4__ {int opercnt; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int /*<<< orphan*/  hil_mlc_send_polls (TYPE_1__*) ; 
 scalar_t__ hil_mlcs_probe ; 

__attribute__((used)) static int hilse_operate(hil_mlc *mlc, int repoll)
{

	if (mlc->opercnt == 0)
		hil_mlcs_probe = 0;
	mlc->opercnt = 1;

	hil_mlc_send_polls(mlc);

	if (!hil_mlcs_probe)
		return 0;
	hil_mlcs_probe = 0;
	mlc->opercnt = 0;
	return 1;
}