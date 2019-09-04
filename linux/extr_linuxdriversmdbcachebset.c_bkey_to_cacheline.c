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
struct bset_tree {scalar_t__ data; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 int BSET_CACHELINE ; 

__attribute__((used)) static unsigned int bkey_to_cacheline(struct bset_tree *t, struct bkey *k)
{
	return ((void *) k - (void *) t->data) / BSET_CACHELINE;
}