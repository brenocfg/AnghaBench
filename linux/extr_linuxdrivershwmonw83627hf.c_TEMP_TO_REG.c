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
 int /*<<< orphan*/  TEMP_MAX ; 
 int /*<<< orphan*/  TEMP_MIN ; 
 int clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 TEMP_TO_REG(long temp)
{
	int ntemp = clamp_val(temp, TEMP_MIN, TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	return (u8)(ntemp / 1000);
}