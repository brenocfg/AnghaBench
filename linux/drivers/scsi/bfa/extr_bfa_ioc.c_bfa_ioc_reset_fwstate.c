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
struct bfa_ioc_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  bfa_ioc_set_alt_ioc_fwstate (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_set_cur_ioc_fwstate (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 

void
bfa_ioc_reset_fwstate(struct bfa_ioc_s *ioc)
{
	bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_UNINIT);
}