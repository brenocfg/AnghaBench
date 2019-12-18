#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int val; } ;
typedef  TYPE_1__ uint_fixed_16_16_t ;
typedef  int u32 ;

/* Variables and functions */
 int U16_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline uint_fixed_16_16_t u32_to_fixed16(u32 val)
{
	uint_fixed_16_16_t fp = { .val = val << 16 };

	WARN_ON(val > U16_MAX);

	return fp;
}