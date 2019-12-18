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
struct vmballoon {int /*<<< orphan*/  size; } ;
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 struct vmballoon balloon ; 

__attribute__((used)) static unsigned long vmballoon_shrinker_count(struct shrinker *shrinker,
					      struct shrink_control *sc)
{
	struct vmballoon *b = &balloon;

	return atomic64_read(&b->size);
}