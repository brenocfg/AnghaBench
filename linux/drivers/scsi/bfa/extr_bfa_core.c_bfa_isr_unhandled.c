#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i2htok; } ;
struct TYPE_4__ {TYPE_1__ mtag; int /*<<< orphan*/  msg_id; int /*<<< orphan*/  msg_class; } ;
struct bfi_msg_s {TYPE_2__ mhdr; } ;
struct bfa_s {int /*<<< orphan*/  trcmod; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc_stop (int /*<<< orphan*/ ) ; 

void
bfa_isr_unhandled(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	bfa_trc(bfa, m->mhdr.msg_class);
	bfa_trc(bfa, m->mhdr.msg_id);
	bfa_trc(bfa, m->mhdr.mtag.i2htok);
	WARN_ON(1);
	bfa_trc_stop(bfa->trcmod);
}