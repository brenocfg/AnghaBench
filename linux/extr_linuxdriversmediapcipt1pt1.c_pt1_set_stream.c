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
struct pt1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int,int) ; 

__attribute__((used)) static void pt1_set_stream(struct pt1 *pt1, int index, int enabled)
{
	pt1_write_reg(pt1, 2, 1 << (index + 8) | enabled << index);
}