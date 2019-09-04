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
typedef  scalar_t__ u16 ;
typedef  int s16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 

__attribute__((used)) static inline int DS1621_TEMP_FROM_REG(u16 reg)
{
	return DIV_ROUND_CLOSEST(((s16)reg / 16) * 625, 10);
}