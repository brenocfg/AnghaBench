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
struct keylist {scalar_t__ top; scalar_t__ keys; } ;

/* Variables and functions */

__attribute__((used)) static inline bool bch_keylist_empty(struct keylist *l)
{
	return l->top == l->keys;
}