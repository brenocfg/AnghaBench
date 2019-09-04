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
typedef  int /*<<< orphan*/  u32 ;
struct rot_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROT_CONTROL ; 
 int /*<<< orphan*/  ROT_CONTROL_START ; 
 int /*<<< orphan*/  rot_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rot_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotator_reg_set_irq (struct rot_context*,int) ; 

__attribute__((used)) static void rotator_start(struct rot_context *rot)
{
	u32 val;

	/* Set interrupt enable */
	rotator_reg_set_irq(rot, true);

	val = rot_read(ROT_CONTROL);
	val |= ROT_CONTROL_START;
	rot_write(val, ROT_CONTROL);
}