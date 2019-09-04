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
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 int as99127f ; 
 int clamp_val (long,int,int) ; 
 int w83781d ; 

__attribute__((used)) static inline u8
DIV_TO_REG(long val, enum chips type)
{
	int i;
	val = clamp_val(val, 1,
			((type == w83781d || type == as99127f) ? 8 : 128)) >> 1;
	for (i = 0; i < 7; i++) {
		if (val == 0)
			break;
		val >>= 1;
	}
	return i;
}