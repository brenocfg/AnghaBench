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
struct ilist {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; scalar_t__ nr_elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEXER_NULL ; 

__attribute__((used)) static void l_init(struct ilist *l)
{
	l->nr_elts = 0;
	l->head = l->tail = INDEXER_NULL;
}