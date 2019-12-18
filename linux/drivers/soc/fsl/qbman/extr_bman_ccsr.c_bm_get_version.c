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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IP_REV_1 ; 
 int bm_ccsr_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bm_get_version(u16 *id, u8 *major, u8 *minor)
{
	u32 v = bm_ccsr_in(REG_IP_REV_1);
	*id = (v >> 16);
	*major = (v >> 8) & 0xff;
	*minor = v & 0xff;
}