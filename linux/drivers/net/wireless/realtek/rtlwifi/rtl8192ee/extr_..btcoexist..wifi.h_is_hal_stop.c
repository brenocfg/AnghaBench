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
struct rtl_hal {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ _HAL_STATE_STOP ; 

__attribute__((used)) static inline bool is_hal_stop(struct rtl_hal *rtlhal)
{
	return (_HAL_STATE_STOP == rtlhal->state);
}