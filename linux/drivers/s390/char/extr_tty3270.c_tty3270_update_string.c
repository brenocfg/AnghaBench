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
struct TYPE_2__ {int cols; int /*<<< orphan*/  dev; } ;
struct tty3270 {TYPE_1__ view; } ;
struct string {unsigned char* string; int len; } ;

/* Variables and functions */
 unsigned char TO_RA ; 
 int /*<<< orphan*/  raw3270_buffer_address (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void
tty3270_update_string(struct tty3270 *tp, struct string *line, int nr)
{
	unsigned char *cp;

	raw3270_buffer_address(tp->view.dev, line->string + 1,
			       tp->view.cols * nr);
	cp = line->string + line->len - 4;
	if (*cp == TO_RA)
		raw3270_buffer_address(tp->view.dev, cp + 1,
				       tp->view.cols * (nr + 1));
}