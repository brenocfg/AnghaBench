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
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  UML_LONGJMP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ UML_SETJMP (int /*<<< orphan*/ *) ; 

void switch_threads(jmp_buf *me, jmp_buf *you)
{
	if (UML_SETJMP(me) == 0)
		UML_LONGJMP(you, 1);
}