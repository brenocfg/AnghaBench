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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  JC42_TEMP_MAX ; 
 int /*<<< orphan*/  JC42_TEMP_MIN ; 
 int /*<<< orphan*/  JC42_TEMP_MIN_EXTENDED ; 
 int clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 jc42_temp_to_reg(long temp, bool extended)
{
	int ntemp = clamp_val(temp,
			      extended ? JC42_TEMP_MIN_EXTENDED :
			      JC42_TEMP_MIN, JC42_TEMP_MAX);

	/* convert from 0.001 to 0.0625 resolution */
	return (ntemp * 2 / 125) & 0x1fff;
}