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
struct pagevec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  check_move_unevictable_pages (struct pagevec*) ; 
 int /*<<< orphan*/  cond_resched () ; 

__attribute__((used)) static void drm_gem_check_release_pagevec(struct pagevec *pvec)
{
	check_move_unevictable_pages(pvec);
	__pagevec_release(pvec);
	cond_resched();
}