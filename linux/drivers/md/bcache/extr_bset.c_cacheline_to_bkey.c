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
typedef  void bkey ;

/* Variables and functions */
 unsigned int BSET_CACHELINE ; 

__attribute__((used)) static struct bkey *cacheline_to_bkey(struct bset_tree *t,
				      unsigned int cacheline,
				      unsigned int offset)
{
	return ((void *) t->data) + cacheline * BSET_CACHELINE + offset * 8;
}