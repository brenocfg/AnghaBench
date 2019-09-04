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
 unsigned long DR_GLOBAL_SLOWDOWN ; 
 unsigned long __encode_dr7 (int,unsigned int,unsigned int) ; 

unsigned long encode_dr7(int drnum, unsigned int len, unsigned int type)
{
	return __encode_dr7(drnum, len, type) | DR_GLOBAL_SLOWDOWN;
}