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
typedef  int /*<<< orphan*/  u8 ;
struct hantro_h264_reflist_builder {int num_valid; int /*<<< orphan*/  unordered_reflist; } ;

/* Variables and functions */
 int /*<<< orphan*/  b0_ref_list_cmp ; 
 int /*<<< orphan*/  b1_ref_list_cmp ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sort_r (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hantro_h264_reflist_builder const*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_b_ref_lists(const struct hantro_h264_reflist_builder *builder,
		  u8 *b0_reflist, u8 *b1_reflist)
{
	memcpy(b0_reflist, builder->unordered_reflist,
	       sizeof(builder->unordered_reflist));
	sort_r(b0_reflist, builder->num_valid, sizeof(*b0_reflist),
	       b0_ref_list_cmp, NULL, builder);

	memcpy(b1_reflist, builder->unordered_reflist,
	       sizeof(builder->unordered_reflist));
	sort_r(b1_reflist, builder->num_valid, sizeof(*b1_reflist),
	       b1_ref_list_cmp, NULL, builder);

	if (builder->num_valid > 1 &&
	    !memcmp(b1_reflist, b0_reflist, builder->num_valid))
		swap(b1_reflist[0], b1_reflist[1]);
}