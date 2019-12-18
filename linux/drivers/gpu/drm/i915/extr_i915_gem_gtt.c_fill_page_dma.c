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
typedef  int /*<<< orphan*/  u64 ;
struct i915_page_dma {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const,unsigned int) ; 

__attribute__((used)) static void
fill_page_dma(const struct i915_page_dma *p, const u64 val, unsigned int count)
{
	kunmap_atomic(memset64(kmap_atomic(p->page), val, count));
}