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
struct btree_keys {int dummy; } ;
struct bset {int dummy; } ;

/* Variables and functions */
 int bset_byte_offset (struct btree_keys*,struct bset*) ; 

__attribute__((used)) static inline unsigned int bset_sector_offset(struct btree_keys *b,
					      struct bset *i)
{
	return bset_byte_offset(b, i) >> 9;
}