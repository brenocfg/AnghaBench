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
typedef  int /*<<< orphan*/  uint64_t ;
struct keylist {int dummy; } ;

/* Variables and functions */
 int bch_keylist_nkeys (struct keylist*) ; 

__attribute__((used)) static inline size_t bch_keylist_bytes(struct keylist *l)
{
	return bch_keylist_nkeys(l) * sizeof(uint64_t);
}