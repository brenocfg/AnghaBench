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
struct TYPE_4__ {scalar_t__ type; scalar_t__ id; scalar_t__ off; } ;
struct TYPE_3__ {scalar_t__ off; } ;
struct nfp_insn_meta {TYPE_2__ ptr; TYPE_1__ insn; } ;
struct bpf_insn {scalar_t__ off; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */

__attribute__((used)) static bool
cross_mem_access(struct bpf_insn *ld, struct nfp_insn_meta *head_ld_meta,
		 struct nfp_insn_meta *head_st_meta)
{
	s16 head_ld_off, head_st_off, ld_off;

	/* Different pointer types does not overlap. */
	if (head_ld_meta->ptr.type != head_st_meta->ptr.type)
		return false;

	/* load and store are both PTR_TO_PACKET, check ID info.  */
	if (head_ld_meta->ptr.id != head_st_meta->ptr.id)
		return true;

	/* Canonicalize the offsets. Turn all of them against the original
	 * base register.
	 */
	head_ld_off = head_ld_meta->insn.off + head_ld_meta->ptr.off;
	head_st_off = head_st_meta->insn.off + head_st_meta->ptr.off;
	ld_off = ld->off + head_ld_meta->ptr.off;

	/* Ascending order cross. */
	if (ld_off > head_ld_off &&
	    head_ld_off < head_st_off && ld_off >= head_st_off)
		return true;

	/* Descending order cross. */
	if (ld_off < head_ld_off &&
	    head_ld_off > head_st_off && ld_off <= head_st_off)
		return true;

	return false;
}