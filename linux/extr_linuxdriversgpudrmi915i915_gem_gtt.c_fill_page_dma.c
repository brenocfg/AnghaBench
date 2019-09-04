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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u64 ;
struct i915_page_dma {int /*<<< orphan*/  page; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  memset64 (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void fill_page_dma(struct i915_address_space *vm,
			  struct i915_page_dma *p,
			  const u64 val)
{
	u64 * const vaddr = kmap_atomic(p->page);

	memset64(vaddr, val, PAGE_SIZE / sizeof(val));

	kunmap_atomic(vaddr);
}