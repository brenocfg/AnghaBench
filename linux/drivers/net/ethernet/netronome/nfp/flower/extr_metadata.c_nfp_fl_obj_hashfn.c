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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_fl_payload {int /*<<< orphan*/  tc_flower_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nfp_fl_obj_hashfn(const void *data, u32 len, u32 seed)
{
	const struct nfp_fl_payload *flower_entry = data;

	return jhash2((u32 *)&flower_entry->tc_flower_cookie,
		      sizeof(flower_entry->tc_flower_cookie) / sizeof(u32),
		      seed);
}