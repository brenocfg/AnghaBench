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
 scalar_t__ KEY_CSUM (struct bkey const*) ; 
 scalar_t__ KEY_DIRTY (struct bkey const*) ; 
 scalar_t__ KEY_PTRS (struct bkey const*) ; 

__attribute__((used)) static inline bool bch_bkey_equal_header(const struct bkey *l,
					 const struct bkey *r)
{
	return (KEY_DIRTY(l) == KEY_DIRTY(r) &&
		KEY_PTRS(l) == KEY_PTRS(r) &&
		KEY_CSUM(l) == KEY_CSUM(r));
}