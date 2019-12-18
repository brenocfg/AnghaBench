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
struct ed {int /*<<< orphan*/  node; int /*<<< orphan*/  td_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ed*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_ed(struct ed *ed)
{
	memset(ed, 0, sizeof(*ed));
	INIT_LIST_HEAD(&ed->td_list);
	INIT_LIST_HEAD(&ed->node);
}