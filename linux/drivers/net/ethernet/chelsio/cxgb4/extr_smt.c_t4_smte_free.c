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
struct smt_entry {scalar_t__ refcnt; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMT_STATE_UNUSED ; 

__attribute__((used)) static void t4_smte_free(struct smt_entry *e)
{
	if (e->refcnt == 0) {  /* hasn't been recycled */
		e->state = SMT_STATE_UNUSED;
	}
}