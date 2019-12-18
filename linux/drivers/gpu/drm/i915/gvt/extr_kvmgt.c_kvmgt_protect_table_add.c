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
struct kvmgt_pgfn {int /*<<< orphan*/  hnode; int /*<<< orphan*/  gfn; } ;
struct kvmgt_guest_info {int /*<<< orphan*/  ptable; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kvmgt_gfn_is_write_protected (struct kvmgt_guest_info*,int /*<<< orphan*/ ) ; 
 struct kvmgt_pgfn* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmgt_protect_table_add(struct kvmgt_guest_info *info, gfn_t gfn)
{
	struct kvmgt_pgfn *p;

	if (kvmgt_gfn_is_write_protected(info, gfn))
		return;

	p = kzalloc(sizeof(struct kvmgt_pgfn), GFP_ATOMIC);
	if (WARN(!p, "gfn: 0x%llx\n", gfn))
		return;

	p->gfn = gfn;
	hash_add(info->ptable, &p->hnode, gfn);
}