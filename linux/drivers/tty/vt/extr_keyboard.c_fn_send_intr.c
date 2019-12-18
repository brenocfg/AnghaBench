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
struct vc_data {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fn_send_intr(struct vc_data *vc)
{
	tty_insert_flip_char(&vc->port, 0, TTY_BREAK);
	tty_schedule_flip(&vc->port);
}