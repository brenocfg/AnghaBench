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
struct fbcon_ops {scalar_t__ rotate; int /*<<< orphan*/ * rotate_font; int /*<<< orphan*/  update_start; int /*<<< orphan*/  cursor; int /*<<< orphan*/  clear_margins; int /*<<< orphan*/  putcs; int /*<<< orphan*/  clear; int /*<<< orphan*/  bmove; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_bmove ; 
 int /*<<< orphan*/  bit_clear ; 
 int /*<<< orphan*/  bit_clear_margins ; 
 int /*<<< orphan*/  bit_cursor ; 
 int /*<<< orphan*/  bit_putcs ; 
 int /*<<< orphan*/  bit_update_start ; 
 int /*<<< orphan*/  fbcon_set_rotate (struct fbcon_ops*) ; 

void fbcon_set_bitops(struct fbcon_ops *ops)
{
	ops->bmove = bit_bmove;
	ops->clear = bit_clear;
	ops->putcs = bit_putcs;
	ops->clear_margins = bit_clear_margins;
	ops->cursor = bit_cursor;
	ops->update_start = bit_update_start;
	ops->rotate_font = NULL;

	if (ops->rotate)
		fbcon_set_rotate(ops);
}