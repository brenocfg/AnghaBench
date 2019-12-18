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

/* Variables and functions */
 scalar_t__ ps3_compare_firmware_version (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int precise_ie(void)
{
	return 0 <= ps3_compare_firmware_version(2, 2, 0);
}