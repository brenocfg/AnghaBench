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
struct intel_engine_execlists {scalar_t__ active; } ;

/* Variables and functions */

__attribute__((used)) static inline void
execlists_clear_all_active(struct intel_engine_execlists *execlists)
{
	execlists->active = 0;
}