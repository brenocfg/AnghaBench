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

/* Variables and functions */
 int /*<<< orphan*/  put_user_pages_dirty_lock (struct page**,size_t,int) ; 

__attribute__((used)) static void __qib_release_user_pages(struct page **p, size_t num_pages,
				     int dirty)
{
	put_user_pages_dirty_lock(p, num_pages, dirty);
}