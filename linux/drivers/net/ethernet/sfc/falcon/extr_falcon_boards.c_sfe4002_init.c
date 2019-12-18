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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int ef4_init_lm87 (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe4002_hwmon_info ; 
 int /*<<< orphan*/  sfe4002_lm87_regs ; 

__attribute__((used)) static int sfe4002_init(struct ef4_nic *efx)
{
	return ef4_init_lm87(efx, &sfe4002_hwmon_info, sfe4002_lm87_regs);
}