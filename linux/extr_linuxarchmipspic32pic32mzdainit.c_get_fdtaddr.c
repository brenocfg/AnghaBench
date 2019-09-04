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
typedef  scalar_t__ ulong ;

/* Variables and functions */
 scalar_t__ __dtb_end ; 
 scalar_t__ __dtb_start ; 
 int /*<<< orphan*/  fw_arg2 ; 
 int /*<<< orphan*/  fw_arg3 ; 
 scalar_t__ fw_passed_dtb ; 

__attribute__((used)) static ulong get_fdtaddr(void)
{
	ulong ftaddr = 0;

	if (fw_passed_dtb && !fw_arg2 && !fw_arg3)
		return (ulong)fw_passed_dtb;

	if (__dtb_start < __dtb_end)
		ftaddr = (ulong)__dtb_start;

	return ftaddr;
}