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
struct page_list {int dummy; } ;
struct dpages {unsigned int context_u; struct page_list* context_ptr; int /*<<< orphan*/  next_page; int /*<<< orphan*/  get_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_get_page ; 
 int /*<<< orphan*/  list_next_page ; 

__attribute__((used)) static void list_dp_init(struct dpages *dp, struct page_list *pl, unsigned offset)
{
	dp->get_page = list_get_page;
	dp->next_page = list_next_page;
	dp->context_u = offset;
	dp->context_ptr = pl;
}