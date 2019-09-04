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
struct uasm_label {int lab; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */

void uasm_build_label(struct uasm_label **lab, u32 *addr, int lid)
{
	(*lab)->addr = addr;
	(*lab)->lab = lid;
	(*lab)++;
}