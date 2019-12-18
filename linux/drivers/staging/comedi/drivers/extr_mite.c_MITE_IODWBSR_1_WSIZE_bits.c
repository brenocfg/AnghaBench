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
 int ilog2 (unsigned int) ; 

__attribute__((used)) static unsigned int MITE_IODWBSR_1_WSIZE_bits(unsigned int size)
{
	return (ilog2(size) - 1) & 0x1f;
}