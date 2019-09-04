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
typedef  int u16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int TMP401_CONFIG_RANGE ; 
 long clamp_val (long,int,int) ; 

__attribute__((used)) static u16 tmp401_temp_to_register(long temp, u8 config, int zbits)
{
	if (config & TMP401_CONFIG_RANGE) {
		temp = clamp_val(temp, -64000, 191000);
		temp += 64000;
	} else
		temp = clamp_val(temp, 0, 127000);

	return DIV_ROUND_CLOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
}