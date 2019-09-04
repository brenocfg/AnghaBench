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
struct mm_walk {struct mm_struct* mm; int /*<<< orphan*/  pmd_entry; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  __zap_zero_pages ; 
 int /*<<< orphan*/  walk_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 

__attribute__((used)) static inline void zap_zero_pages(struct mm_struct *mm)
{
	struct mm_walk walk = { .pmd_entry = __zap_zero_pages };

	walk.mm = mm;
	walk_page_range(0, TASK_SIZE, &walk);
}