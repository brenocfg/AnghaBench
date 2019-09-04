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
struct ubi_attach_info {int dummy; } ;
struct ubi_ainf_peb {int /*<<< orphan*/  copy_flag; int /*<<< orphan*/  scrub; int /*<<< orphan*/  lnum; int /*<<< orphan*/  sqnum; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; } ;

/* Variables and functions */
 struct ubi_ainf_peb* ubi_alloc_aeb (struct ubi_attach_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ubi_ainf_peb *clone_aeb(struct ubi_attach_info *ai,
				      struct ubi_ainf_peb *old)
{
	struct ubi_ainf_peb *new;

	new = ubi_alloc_aeb(ai, old->pnum, old->ec);
	if (!new)
		return NULL;

	new->vol_id = old->vol_id;
	new->sqnum = old->sqnum;
	new->lnum = old->lnum;
	new->scrub = old->scrub;
	new->copy_flag = old->copy_flag;

	return new;
}