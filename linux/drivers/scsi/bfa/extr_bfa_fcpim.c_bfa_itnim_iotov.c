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
struct bfa_itnim_s {int /*<<< orphan*/  ditn; int /*<<< orphan*/  iotov_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  bfa_cb_itnim_tov (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_cb_itnim_tov_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_itnim_iotov_cleanup (struct bfa_itnim_s*) ; 

__attribute__((used)) static void
bfa_itnim_iotov(void *itnim_arg)
{
	struct bfa_itnim_s *itnim = itnim_arg;

	itnim->iotov_active = BFA_FALSE;

	bfa_cb_itnim_tov_begin(itnim->ditn);
	bfa_itnim_iotov_cleanup(itnim);
	bfa_cb_itnim_tov(itnim->ditn);
}