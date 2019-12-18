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
struct tty3270 {scalar_t__ cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty3270_convert_line (struct tty3270*,scalar_t__) ; 

__attribute__((used)) static void
tty3270_ri(struct tty3270 *tp)
{
	if (tp->cy > 0) {
	    tty3270_convert_line(tp, tp->cy);
	    tp->cy--;
	}
}