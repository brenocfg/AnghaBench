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
struct venus_core {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_V3 (struct venus_core*) ; 
 scalar_t__ IS_V4 (struct venus_core*) ; 
 int venus_suspend_1xx (struct venus_core*) ; 
 int venus_suspend_3xx (struct venus_core*) ; 

__attribute__((used)) static int venus_suspend(struct venus_core *core)
{
	if (IS_V3(core) || IS_V4(core))
		return venus_suspend_3xx(core);

	return venus_suspend_1xx(core);
}