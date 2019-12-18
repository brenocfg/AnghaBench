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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  enum cxd2841er_xtal { ____Placeholder_cxd2841er_xtal } cxd2841er_xtal ;

/* Variables and functions */
 int SONY_XTAL_24000 ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 cxd2841er_calc_iffreq_xtal(enum cxd2841er_xtal xtal, u32 ifhz)
{
	u64 tmp;

	tmp = (u64) ifhz * 16777216;
	do_div(tmp, ((xtal == SONY_XTAL_24000) ? 48000000 : 41000000));

	return (u32) tmp;
}