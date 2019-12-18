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
struct siw_page_chunk {int /*<<< orphan*/  plist; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_user_pages_dirty_lock (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void siw_free_plist(struct siw_page_chunk *chunk, int num_pages,
			   bool dirty)
{
	put_user_pages_dirty_lock(chunk->plist, num_pages, dirty);
}