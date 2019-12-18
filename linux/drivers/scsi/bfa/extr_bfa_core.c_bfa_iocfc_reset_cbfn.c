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
struct bfa_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_iocfc_reset_queues (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_isr_enable (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_reset_cbfn(void *bfa_arg)
{
	struct bfa_s	*bfa = bfa_arg;

	bfa_iocfc_reset_queues(bfa);
	bfa_isr_enable(bfa);
}