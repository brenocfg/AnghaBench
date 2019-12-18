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
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __GFP_COMP ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_order (scalar_t__) ; 

__attribute__((used)) static inline struct page *be_alloc_pages(u32 size, gfp_t gfp)
{
	u32 order = get_order(size);

	if (order > 0)
		gfp |= __GFP_COMP;
	return  alloc_pages(gfp, order);
}