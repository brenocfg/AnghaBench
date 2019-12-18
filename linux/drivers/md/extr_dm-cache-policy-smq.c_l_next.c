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
struct entry_space {int dummy; } ;
struct entry {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct entry* to_entry (struct entry_space*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *l_next(struct entry_space *es, struct entry *e)
{
	return to_entry(es, e->next);
}