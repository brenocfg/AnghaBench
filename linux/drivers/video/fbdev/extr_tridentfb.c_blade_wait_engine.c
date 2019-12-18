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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readmmr (struct tridentfb_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blade_wait_engine(struct tridentfb_par *par)
{
	while (readmmr(par, STATUS) & 0xFA800000)
		cpu_relax();
}