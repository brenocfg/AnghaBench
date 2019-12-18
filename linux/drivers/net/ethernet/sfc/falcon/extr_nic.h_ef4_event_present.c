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
struct TYPE_3__ {int /*<<< orphan*/ * dword; } ;
typedef  TYPE_1__ ef4_qword_t ;

/* Variables and functions */
 int EF4_DWORD_IS_ALL_ONES (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ef4_event_present(ef4_qword_t *event)
{
	return !(EF4_DWORD_IS_ALL_ONES(event->dword[0]) |
		  EF4_DWORD_IS_ALL_ONES(event->dword[1]));
}