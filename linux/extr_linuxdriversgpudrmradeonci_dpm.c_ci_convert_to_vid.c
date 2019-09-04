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
 int VOLTAGE_SCALE ; 

__attribute__((used)) static u8 ci_convert_to_vid(u16 vddc)
{
	return (6200 - (vddc * VOLTAGE_SCALE)) / 25;
}