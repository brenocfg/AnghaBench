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
struct ptp_clock_info {int dummy; } ;
typedef  enum ptp_pin_function { ____Placeholder_ptp_pin_function } ptp_pin_function ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int PTP_PF_PHYSYNC ; 

__attribute__((used)) static int mlx5_ptp_verify(struct ptp_clock_info *ptp, unsigned int pin,
			   enum ptp_pin_function func, unsigned int chan)
{
	return (func == PTP_PF_PHYSYNC) ? -EOPNOTSUPP : 0;
}