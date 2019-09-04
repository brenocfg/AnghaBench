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
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7X10_TEMP_MAX ; 
 int /*<<< orphan*/  ADT7X10_TEMP_MIN ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int) ; 
 int clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s16 ADT7X10_TEMP_TO_REG(long temp)
{
	return DIV_ROUND_CLOSEST(clamp_val(temp, ADT7X10_TEMP_MIN,
					       ADT7X10_TEMP_MAX) * 128, 1000);
}