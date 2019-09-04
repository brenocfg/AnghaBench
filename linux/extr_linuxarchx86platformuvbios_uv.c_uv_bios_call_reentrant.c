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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum uv_bios_cmd { ____Placeholder_uv_bios_cmd } uv_bios_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  uv_bios_call (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s64 uv_bios_call_reentrant(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
					u64 a4, u64 a5)
{
	s64 ret;

	preempt_disable();
	ret = uv_bios_call(which, a1, a2, a3, a4, a5);
	preempt_enable();

	return ret;
}