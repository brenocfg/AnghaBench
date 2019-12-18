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
struct pm3_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM3InFIFOSpace ; 
 scalar_t__ PM3_READ_REG (struct pm3_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static inline void PM3_WAIT(struct pm3_par *par, u32 n)
{
	while (PM3_READ_REG(par, PM3InFIFOSpace) < n)
		cpu_relax();
}