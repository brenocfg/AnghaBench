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
typedef  int uint64_t ;
struct bkey {int* ptr; } ;

/* Variables and functions */
 size_t KEY_PTRS (struct bkey*) ; 

__attribute__((used)) static uint64_t merge_chksums(struct bkey *l, struct bkey *r)
{
	return (l->ptr[KEY_PTRS(l)] + r->ptr[KEY_PTRS(r)]) &
		~((uint64_t)1 << 63);
}