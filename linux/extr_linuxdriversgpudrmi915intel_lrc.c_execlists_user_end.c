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
struct intel_engine_execlists {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_USER ; 
 int /*<<< orphan*/  execlists_clear_active (struct intel_engine_execlists*,int /*<<< orphan*/ ) ; 

inline void
execlists_user_end(struct intel_engine_execlists *execlists)
{
	execlists_clear_active(execlists, EXECLISTS_ACTIVE_USER);
}