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
typedef  scalar_t__ bits64 ;

/* Variables and functions */

void
sub128(bits64 a0, bits64 a1, bits64 b0, bits64 b1, bits64 * z0Ptr,
       bits64 * z1Ptr)
{
	*z1Ptr = a1 - b1;
	*z0Ptr = a0 - b0 - (a1 < b1);
}