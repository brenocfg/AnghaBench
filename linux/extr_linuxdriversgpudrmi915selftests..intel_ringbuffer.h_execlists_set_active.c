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
struct intel_engine_execlists {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static inline void
execlists_set_active(struct intel_engine_execlists *execlists,
		     unsigned int bit)
{
	__set_bit(bit, (unsigned long *)&execlists->active);
}