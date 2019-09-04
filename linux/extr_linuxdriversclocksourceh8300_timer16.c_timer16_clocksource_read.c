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
typedef  unsigned long u64 ;
struct timer16_priv {unsigned long total_cycles; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 struct timer16_priv* cs_to_priv (struct clocksource*) ; 
 unsigned long timer16_get_counter (struct timer16_priv*) ; 

__attribute__((used)) static u64 timer16_clocksource_read(struct clocksource *cs)
{
	struct timer16_priv *p = cs_to_priv(cs);
	unsigned long raw, value;

	value = p->total_cycles;
	raw = timer16_get_counter(p);

	return value + raw;
}