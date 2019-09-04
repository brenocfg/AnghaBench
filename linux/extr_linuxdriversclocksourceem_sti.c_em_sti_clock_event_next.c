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
typedef  int u64 ;
struct em_sti_priv {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 struct em_sti_priv* ced_to_em_sti (struct clock_event_device*) ; 
 int em_sti_count (struct em_sti_priv*) ; 
 int em_sti_set_next (struct em_sti_priv*,int) ; 

__attribute__((used)) static int em_sti_clock_event_next(unsigned long delta,
				   struct clock_event_device *ced)
{
	struct em_sti_priv *p = ced_to_em_sti(ced);
	u64 next;
	int safe;

	next = em_sti_set_next(p, em_sti_count(p) + delta);
	safe = em_sti_count(p) < (next - 1);

	return !safe;
}