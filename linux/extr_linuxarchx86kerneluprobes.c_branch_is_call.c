#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int opc1; } ;
struct arch_uprobe {TYPE_1__ branch; } ;

/* Variables and functions */

__attribute__((used)) static bool branch_is_call(struct arch_uprobe *auprobe)
{
	return auprobe->branch.opc1 == 0xe8;
}