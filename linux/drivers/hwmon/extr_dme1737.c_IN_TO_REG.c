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
 int DIV_ROUND_CLOSEST (long,int) ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int IN_TO_REG(long val, int nominal)
{
	val = clamp_val(val, 0, 255 * nominal / 192);
	return DIV_ROUND_CLOSEST(val * 192, nominal);
}