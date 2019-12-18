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
struct bfa_ioc {int /*<<< orphan*/  iocpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCPF_E_DISABLE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_disable(struct bfa_ioc *ioc)
{
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_DISABLE);
}