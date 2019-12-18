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
typedef  int u8 ;
typedef  enum lp8788_int_id { ____Placeholder_lp8788_int_id } lp8788_int_id ;

/* Variables and functions */
 int SIZE_REG ; 

__attribute__((used)) static inline u8 _irq_to_mask(enum lp8788_int_id id)
{
	return 1 << (id % SIZE_REG);
}