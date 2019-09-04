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
typedef  int /*<<< orphan*/  diva_man_var_header_t ;
typedef  scalar_t__ byte ;

/* Variables and functions */
 scalar_t__ ESC ; 

__attribute__((used)) static diva_man_var_header_t *get_next_var(diva_man_var_header_t *pVar) {
	byte *msg = (byte *)pVar;
	byte *start;
	int msg_length;

	if (*msg != ESC) return NULL;

	start = msg + 2;
	msg_length = *(msg + 1);
	msg = (start + msg_length);

	if (*msg != ESC) return NULL;

	return ((diva_man_var_header_t *)msg);
}