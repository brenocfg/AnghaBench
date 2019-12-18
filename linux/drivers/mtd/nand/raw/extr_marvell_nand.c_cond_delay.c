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

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  ndelay (unsigned int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cond_delay(unsigned int ns)
{
	if (!ns)
		return;

	if (ns < 10000)
		ndelay(ns);
	else
		udelay(DIV_ROUND_UP(ns, 1000));
}