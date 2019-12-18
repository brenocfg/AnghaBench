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
typedef  int /*<<< orphan*/  u64 ;
struct bset_tree {int dummy; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 scalar_t__ cacheline_to_bkey (struct bset_tree*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int bkey_to_cacheline_offset(struct bset_tree *t,
					 unsigned int cacheline,
					 struct bkey *k)
{
	return (u64 *) k - (u64 *) cacheline_to_bkey(t, cacheline, 0);
}