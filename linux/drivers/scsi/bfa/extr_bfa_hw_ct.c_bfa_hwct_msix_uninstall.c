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
struct TYPE_2__ {int /*<<< orphan*/ * handler; } ;
struct bfa_s {TYPE_1__ msix; } ;

/* Variables and functions */
 int BFI_MSIX_CT_MAX ; 
 int /*<<< orphan*/  bfa_hwct_msix_dummy ; 

void
bfa_hwct_msix_uninstall(struct bfa_s *bfa)
{
	int i;

	for (i = 0; i < BFI_MSIX_CT_MAX; i++)
		bfa->msix.handler[i] = bfa_hwct_msix_dummy;
}