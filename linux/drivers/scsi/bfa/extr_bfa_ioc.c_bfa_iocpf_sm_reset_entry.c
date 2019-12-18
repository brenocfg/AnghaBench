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
struct bfa_iocpf_s {int /*<<< orphan*/  auto_recover; int /*<<< orphan*/  fw_mismatch_notified; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  bfa_auto_recover ; 

__attribute__((used)) static void
bfa_iocpf_sm_reset_entry(struct bfa_iocpf_s *iocpf)
{
	iocpf->fw_mismatch_notified = BFA_FALSE;
	iocpf->auto_recover = bfa_auto_recover;
}