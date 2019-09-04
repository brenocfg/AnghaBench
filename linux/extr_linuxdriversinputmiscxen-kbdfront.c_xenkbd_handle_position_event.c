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
struct xenkbd_position {int rel_z; int /*<<< orphan*/  abs_y; int /*<<< orphan*/  abs_x; } ;
struct xenkbd_info {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xenkbd_handle_position_event(struct xenkbd_info *info,
					 struct xenkbd_position *pos)
{
	if (unlikely(!info->ptr))
		return;

	input_report_abs(info->ptr, ABS_X, pos->abs_x);
	input_report_abs(info->ptr, ABS_Y, pos->abs_y);
	if (pos->rel_z)
		input_report_rel(info->ptr, REL_WHEEL, -pos->rel_z);
	input_sync(info->ptr);
}