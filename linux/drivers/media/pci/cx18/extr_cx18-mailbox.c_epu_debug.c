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
struct TYPE_2__ {int /*<<< orphan*/ * args; } ;
struct cx18_in_work_order {char* str; TYPE_1__ mb; } ;
struct cx18 {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CX18_F_I_LOADED_FW ; 
 int /*<<< orphan*/  CX18_INFO (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void epu_debug(struct cx18 *cx, struct cx18_in_work_order *order)
{
	char *p;
	char *str = order->str;

	CX18_DEBUG_INFO("%x %s\n", order->mb.args[0], str);
	p = strchr(str, '.');
	if (!test_bit(CX18_F_I_LOADED_FW, &cx->i_flags) && p && p > str)
		CX18_INFO("FW version: %s\n", p - 1);
}