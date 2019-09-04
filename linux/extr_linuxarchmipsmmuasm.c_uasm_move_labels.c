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
struct uasm_label {scalar_t__ lab; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 scalar_t__ UASM_LABEL_INVALID ; 

void uasm_move_labels(struct uasm_label *lab, u32 *first, u32 *end,
			       long off)
{
	for (; lab->lab != UASM_LABEL_INVALID; lab++)
		if (lab->addr >= first && lab->addr < end)
			lab->addr += off;
}