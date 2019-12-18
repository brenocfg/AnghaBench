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
struct tty3270_line {struct tty3270_line* cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tty3270_line*) ; 

__attribute__((used)) static void
tty3270_free_screen(struct tty3270_line *screen, unsigned int rows)
{
	int lines;

	for (lines = 0; lines < rows - 2; lines++)
		kfree(screen[lines].cells);
	kfree(screen);
}