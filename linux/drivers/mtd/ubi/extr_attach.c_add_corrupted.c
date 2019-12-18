#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_attach_info {int corr_peb_count; int /*<<< orphan*/  corr; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ubi_ainf_peb {TYPE_1__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dbg_bld (char*,int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ubi_ainf_peb* ubi_alloc_aeb (struct ubi_attach_info*,int,int) ; 

__attribute__((used)) static int add_corrupted(struct ubi_attach_info *ai, int pnum, int ec)
{
	struct ubi_ainf_peb *aeb;

	dbg_bld("add to corrupted: PEB %d, EC %d", pnum, ec);

	aeb = ubi_alloc_aeb(ai, pnum, ec);
	if (!aeb)
		return -ENOMEM;

	ai->corr_peb_count += 1;
	list_add(&aeb->u.list, &ai->corr);
	return 0;
}