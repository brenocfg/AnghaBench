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
struct ppn_set {int /*<<< orphan*/  consume_ppns; int /*<<< orphan*/  produce_ppns; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ppn_set*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qp_free_ppn_set(struct ppn_set *ppn_set)
{
	if (ppn_set->initialized) {
		/* Do not call these functions on NULL inputs. */
		kfree(ppn_set->produce_ppns);
		kfree(ppn_set->consume_ppns);
	}
	memset(ppn_set, 0, sizeof(*ppn_set));
}