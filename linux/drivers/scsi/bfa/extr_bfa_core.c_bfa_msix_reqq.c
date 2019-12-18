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
struct TYPE_3__ {scalar_t__ cpe_vec_q0; } ;
struct TYPE_4__ {TYPE_1__ hwif; } ;
struct bfa_s {TYPE_2__ iocfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_isr_reqq (struct bfa_s*,scalar_t__) ; 

void
bfa_msix_reqq(struct bfa_s *bfa, int vec)
{
	bfa_isr_reqq(bfa, vec - bfa->iocfc.hwif.cpe_vec_q0);
}