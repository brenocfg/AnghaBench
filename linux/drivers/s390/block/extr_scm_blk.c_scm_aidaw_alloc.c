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
struct page {int dummy; } ;
struct aidaw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  aidaw_pool ; 
 struct page* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aidaw* page_address (struct page*) ; 

__attribute__((used)) static inline struct aidaw *scm_aidaw_alloc(void)
{
	struct page *page = mempool_alloc(aidaw_pool, GFP_ATOMIC);

	return page ? page_address(page) : NULL;
}