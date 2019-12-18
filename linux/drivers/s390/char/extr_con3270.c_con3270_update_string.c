#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string {int len; scalar_t__* string; } ;
struct TYPE_2__ {int cols; int /*<<< orphan*/  dev; } ;
struct con3270 {TYPE_1__ view; } ;

/* Variables and functions */
 scalar_t__ TO_RA ; 
 int /*<<< orphan*/  raw3270_buffer_address (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
con3270_update_string(struct con3270 *cp, struct string *s, int nr)
{
	if (s->len < 4) {
		/* This indicates a bug, but printing a warning would
		 * cause a deadlock. */
		return;
	}
	if (s->string[s->len - 4] != TO_RA)
		return;
	raw3270_buffer_address(cp->view.dev, s->string + s->len - 3,
			       cp->view.cols * (nr + 1));
}