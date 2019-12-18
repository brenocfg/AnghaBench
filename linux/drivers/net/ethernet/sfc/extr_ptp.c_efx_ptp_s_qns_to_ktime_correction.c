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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (scalar_t__,int) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t efx_ptp_s_qns_to_ktime_correction(u32 nic_major, u32 nic_minor,
						 s32 correction)
{
	ktime_t kt;

	nic_minor = DIV_ROUND_CLOSEST(nic_minor, 4);
	correction = DIV_ROUND_CLOSEST(correction, 4);

	kt = ktime_set(nic_major, nic_minor);

	if (correction >= 0)
		kt = ktime_add_ns(kt, (u64)correction);
	else
		kt = ktime_sub_ns(kt, (u64)-correction);
	return kt;
}