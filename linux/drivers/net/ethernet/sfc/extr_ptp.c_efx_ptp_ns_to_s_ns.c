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
typedef  scalar_t__ u32 ;
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ptp_ns_to_s_ns(s64 ns, u32 *nic_major, u32 *nic_minor)
{
	struct timespec64 ts = ns_to_timespec64(ns);
	*nic_major = (u32)ts.tv_sec;
	*nic_minor = ts.tv_nsec;
}