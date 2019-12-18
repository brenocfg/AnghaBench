#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 TYPE_1__* PTR_BUCKET (struct cache_set*,struct bkey const*,unsigned int) ; 
 int /*<<< orphan*/  PTR_GEN (struct bkey const*,unsigned int) ; 
 int /*<<< orphan*/  gen_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t ptr_stale(struct cache_set *c, const struct bkey *k,
				unsigned int i)
{
	return gen_after(PTR_BUCKET(c, k, i)->gen, PTR_GEN(k, i));
}