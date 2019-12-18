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
typedef  int u16 ;

/* Variables and functions */
#define  MLX5_EVENT_TYPE_PORT_CHANGE 128 

__attribute__((used)) static bool is_legacy_unaffiliated_event_num(u16 event_num)
{
	switch (event_num) {
	case MLX5_EVENT_TYPE_PORT_CHANGE:
		return true;
	default:
		return false;
	}
}