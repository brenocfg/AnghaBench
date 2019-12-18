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
struct string {int len; int /*<<< orphan*/  update; int /*<<< orphan*/  list; scalar_t__* string; } ;
struct TYPE_3__ {int cols; scalar_t__* ascebc; } ;
struct con3270 {TYPE_2__* cline; TYPE_1__ view; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  update; int /*<<< orphan*/  list; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ TO_RA ; 
 struct string* con3270_alloc_string (struct con3270*,unsigned int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
con3270_cline_end(struct con3270 *cp)
{
	struct string *s;
	unsigned int size;

	/* Copy cline. */
	size = (cp->cline->len < cp->view.cols - 5) ?
		cp->cline->len + 4 : cp->view.cols;
	s = con3270_alloc_string(cp, size);
	memcpy(s->string, cp->cline->string, cp->cline->len);
	if (cp->cline->len < cp->view.cols - 5) {
		s->string[s->len - 4] = TO_RA;
		s->string[s->len - 1] = 0;
	} else {
		while (--size >= cp->cline->len)
			s->string[size] = cp->view.ascebc[' '];
	}
	/* Replace cline with allocated line s and reset cline. */
	list_add(&s->list, &cp->cline->list);
	list_del_init(&cp->cline->list);
	if (!list_empty(&cp->cline->update)) {
		list_add(&s->update, &cp->cline->update);
		list_del_init(&cp->cline->update);
	}
	cp->cline->len = 0;
}