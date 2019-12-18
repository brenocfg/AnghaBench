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
typedef  int /*<<< orphan*/  u32 ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MSIX_RME_QMAX_CB ; 
 int /*<<< orphan*/  BFI_MSIX_RME_QMIN_CB ; 

void
bfa_hwcb_msix_get_rme_range(struct bfa_s *bfa, u32 *start, u32 *end)
{
	*start = BFI_MSIX_RME_QMIN_CB;
	*end = BFI_MSIX_RME_QMAX_CB;
}