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
struct hantro_h264_reflist_builder {int /*<<< orphan*/  num_valid; int /*<<< orphan*/  unordered_reflist; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_ref_list_cmp ; 
 int /*<<< orphan*/  sort_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hantro_h264_reflist_builder const*) ; 

__attribute__((used)) static void
build_p_ref_list(const struct hantro_h264_reflist_builder *builder,
		 u8 *reflist)
{
	memcpy(reflist, builder->unordered_reflist,
	       sizeof(builder->unordered_reflist));
	sort_r(reflist, builder->num_valid, sizeof(*reflist),
	       p_ref_list_cmp, NULL, builder);
}