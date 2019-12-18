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
typedef  unsigned char const u_int32_t ;

/* Variables and functions */

__attribute__((used)) static inline u_int32_t get_32(const unsigned char *x)
{
	return (x[3] << 24) | (x[2] << 16) | (x[1] << 8) | x[0];
}