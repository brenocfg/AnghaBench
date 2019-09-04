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
 int /*<<< orphan*/  BIOS_STATUS_ABORT ; 
 int /*<<< orphan*/  __efi_uv_runtime_lock ; 
 int /*<<< orphan*/  __uv_bios_call (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

s64 uv_bios_call(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5)
{
	s64 ret;

	if (down_interruptible(&__efi_uv_runtime_lock))
		return BIOS_STATUS_ABORT;

	ret = __uv_bios_call(which, a1, a2, a3, a4, a5);
	up(&__efi_uv_runtime_lock);

	return ret;
}