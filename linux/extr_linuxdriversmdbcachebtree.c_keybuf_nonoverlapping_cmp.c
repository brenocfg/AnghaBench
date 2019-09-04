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
struct keybuf_key {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  int64_t ; 

__attribute__((used)) static inline int keybuf_nonoverlapping_cmp(struct keybuf_key *l,
					    struct keybuf_key *r)
{
	return clamp_t(int64_t, bkey_cmp(&l->key, &r->key), -1, 1);
}