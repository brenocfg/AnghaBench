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
struct page {int dummy; } ;
struct i915_vma {TYPE_1__* pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct page* sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct page *i915_vma_first_page(struct i915_vma *vma)
{
	GEM_BUG_ON(!vma->pages);
	return sg_page(vma->pages->sgl);
}