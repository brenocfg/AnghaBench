#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/ * str; } ;
struct TYPE_6__ {TYPE_1__ str; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ data; } ;
struct TYPE_8__ {TYPE_3__ other_data; } ;
struct detailed_timing {TYPE_4__ data; } ;

/* Variables and functions */
 scalar_t__ EDID_DETAIL_MONITOR_NAME ; 

__attribute__((used)) static void
monitor_name(struct detailed_timing *t, void *data)
{
	if (t->data.other_data.type == EDID_DETAIL_MONITOR_NAME)
		*(u8 **)data = t->data.other_data.data.str.str;
}