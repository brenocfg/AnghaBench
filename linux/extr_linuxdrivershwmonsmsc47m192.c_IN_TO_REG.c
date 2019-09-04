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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE (unsigned long,int,int) ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 int* nom_mv ; 

__attribute__((used)) static inline u8 IN_TO_REG(unsigned long val, int n)
{
	val = clamp_val(val, 0, nom_mv[n] * 255 / 192);
	return SCALE(val, 192, nom_mv[n]);
}