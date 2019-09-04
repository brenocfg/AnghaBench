#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/ * capi_send_handler_t ;
struct TYPE_3__ {scalar_t__ const cmd; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* capi_send_handler_table ; 

__attribute__((used)) static inline capi_send_handler_t lookup_capi_send_handler(const u16 cmd)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(capi_send_handler_table); i++)
		if (capi_send_handler_table[i].cmd == cmd)
			return capi_send_handler_table[i].handler;
	return NULL;
}