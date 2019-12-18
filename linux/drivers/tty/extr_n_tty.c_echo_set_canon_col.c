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
struct n_tty_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO_OP_SET_CANON_COL ; 
 int /*<<< orphan*/  ECHO_OP_START ; 
 int /*<<< orphan*/  add_echo_byte (int /*<<< orphan*/ ,struct n_tty_data*) ; 

__attribute__((used)) static void echo_set_canon_col(struct n_tty_data *ldata)
{
	add_echo_byte(ECHO_OP_START, ldata);
	add_echo_byte(ECHO_OP_SET_CANON_COL, ldata);
}