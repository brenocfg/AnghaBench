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
typedef  int u16 ;
struct ips_driver {int dummy; } ;

/* Variables and functions */
 int MGTA_OFFSET_MASK ; 
 int MGTA_SLOPE_MASK ; 
 int MGTA_SLOPE_SHIFT ; 
 int /*<<< orphan*/  THM_MGTA ; 
 int /*<<< orphan*/  THM_MGTV ; 
 int TV_MASK ; 
 int TV_SHIFT ; 
 int thm_readq (int /*<<< orphan*/ ) ; 
 int thm_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 read_mgtv(struct ips_driver *ips)
{
	u16 ret;
	u64 slope, offset;
	u64 val;

	val = thm_readq(THM_MGTV);
	val = (val & TV_MASK) >> TV_SHIFT;

	slope = offset = thm_readw(THM_MGTA);
	slope = (slope & MGTA_SLOPE_MASK) >> MGTA_SLOPE_SHIFT;
	offset = offset & MGTA_OFFSET_MASK;

	ret = ((val * slope + 0x40) >> 7) + offset;

	return 0; /* MCH temp reporting buggy */
}