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
struct system_device_crosststamp {int dummy; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int get_device_system_crosststamp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct system_device_crosststamp*) ; 
 int /*<<< orphan*/  ptp_kvm_get_time_fn ; 

__attribute__((used)) static int ptp_kvm_getcrosststamp(struct ptp_clock_info *ptp,
				  struct system_device_crosststamp *xtstamp)
{
	return get_device_system_crosststamp(ptp_kvm_get_time_fn, NULL,
					     NULL, xtstamp);
}