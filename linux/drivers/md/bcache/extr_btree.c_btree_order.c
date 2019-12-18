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
struct bkey {int dummy; } ;

/* Variables and functions */
 int KEY_SIZE (struct bkey*) ; 
 int PAGE_SECTORS ; 
 unsigned int ilog2 (int) ; 

__attribute__((used)) static unsigned int btree_order(struct bkey *k)
{
	return ilog2(KEY_SIZE(k) / PAGE_SECTORS ?: 1);
}