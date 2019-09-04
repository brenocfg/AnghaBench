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
struct n2rng {int /*<<< orphan*/ * scratch_control; } ;

/* Variables and functions */
 unsigned long __pa (int /*<<< orphan*/ *) ; 
 unsigned long n2rng_generic_read_control_v2 (unsigned long,int) ; 

__attribute__((used)) static unsigned long n2rng_control_settle_v2(struct n2rng *np, int unit)
{
	unsigned long ra = __pa(&np->scratch_control[0]);

	return n2rng_generic_read_control_v2(ra, unit);
}