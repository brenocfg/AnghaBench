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
typedef  enum TG3_FLAGS { ____Placeholder_TG3_FLAGS } TG3_FLAGS ;

/* Variables and functions */
 int test_bit (int,unsigned long*) ; 

__attribute__((used)) static inline int _tg3_flag(enum TG3_FLAGS flag, unsigned long *bits)
{
	return test_bit(flag, bits);
}