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
typedef  int u16 ;
struct nix_mcast {int next_free_mce; } ;

/* Variables and functions */

__attribute__((used)) static u16 nix_alloc_mce_list(struct nix_mcast *mcast, int count)
{
	int idx;

	if (!mcast)
		return 0;

	idx = mcast->next_free_mce;
	mcast->next_free_mce += count;
	return idx;
}