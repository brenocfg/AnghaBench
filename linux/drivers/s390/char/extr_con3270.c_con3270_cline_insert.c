#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ascebc; } ;
struct con3270 {int /*<<< orphan*/  update_flags; int /*<<< orphan*/  update; TYPE_1__* cline; TYPE_2__ view; } ;
struct TYPE_3__ {int /*<<< orphan*/  update; int /*<<< orphan*/  len; int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_UPDATE_LIST ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
con3270_cline_insert(struct con3270 *cp, unsigned char c)
{
	cp->cline->string[cp->cline->len++] = 
		cp->view.ascebc[(c < ' ') ? ' ' : c];
	if (list_empty(&cp->cline->update)) {
		list_add_tail(&cp->cline->update, &cp->update);
		cp->update_flags |= CON_UPDATE_LIST;
	}
}