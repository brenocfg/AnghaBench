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
struct bfa_iocpf {int fw_mismatch_notified; int /*<<< orphan*/  auto_recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_nw_auto_recover ; 

__attribute__((used)) static void
bfa_iocpf_sm_reset_entry(struct bfa_iocpf *iocpf)
{
	iocpf->fw_mismatch_notified = false;
	iocpf->auto_recover = bfa_nw_auto_recover;
}