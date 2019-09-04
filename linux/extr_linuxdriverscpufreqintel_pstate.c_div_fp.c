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
typedef  scalar_t__ s64 ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int FRAC_BITS ; 
 int /*<<< orphan*/  div64_s64 (int,scalar_t__) ; 

__attribute__((used)) static inline int32_t div_fp(s64 x, s64 y)
{
	return div64_s64((int64_t)x << FRAC_BITS, y);
}