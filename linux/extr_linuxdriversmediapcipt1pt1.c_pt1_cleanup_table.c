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
struct pt1_table {int /*<<< orphan*/  addr; int /*<<< orphan*/  page; int /*<<< orphan*/ * bufs; } ;
struct pt1 {int dummy; } ;

/* Variables and functions */
 int PT1_NR_BUFS ; 
 int /*<<< orphan*/  pt1_cleanup_buffer (struct pt1*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt1_free_page (struct pt1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt1_cleanup_table(struct pt1 *pt1, struct pt1_table *table)
{
	int i;

	for (i = 0; i < PT1_NR_BUFS; i++)
		pt1_cleanup_buffer(pt1, &table->bufs[i]);

	pt1_free_page(pt1, table->page, table->addr);
}