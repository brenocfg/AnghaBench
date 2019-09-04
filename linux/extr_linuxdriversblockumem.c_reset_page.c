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
struct mm_page {int /*<<< orphan*/ * bio; int /*<<< orphan*/ ** biotail; scalar_t__ headcnt; scalar_t__ cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline void reset_page(struct mm_page *page)
{
	page->cnt = 0;
	page->headcnt = 0;
	page->bio = NULL;
	page->biotail = &page->bio;
}