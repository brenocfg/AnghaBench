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
typedef  long u16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/  DS1621_TEMP_MAX ; 
 int /*<<< orphan*/  DS1621_TEMP_MIN ; 
 long clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 DS1621_TEMP_TO_REG(long temp, u8 zbits)
{
	temp = clamp_val(temp, DS1621_TEMP_MIN, DS1621_TEMP_MAX);
	temp = DIV_ROUND_CLOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
	return temp;
}