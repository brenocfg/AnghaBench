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
typedef  int u64 ;
struct i915_syncmap {int height; } ;

/* Variables and functions */
 int SHIFT ; 

__attribute__((used)) static inline u64 __sync_branch_prefix(const struct i915_syncmap *p, u64 id)
{
	return id >> p->height >> SHIFT;
}