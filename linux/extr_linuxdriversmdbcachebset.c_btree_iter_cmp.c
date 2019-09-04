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
struct btree_iter_set {int /*<<< orphan*/  k; } ;

/* Variables and functions */
 scalar_t__ bkey_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool btree_iter_cmp(struct btree_iter_set l,
				  struct btree_iter_set r)
{
	return bkey_cmp(l.k, r.k) > 0;
}