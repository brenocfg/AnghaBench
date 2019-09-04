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
struct timer_list {int dummy; } ;
struct nodepda_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bte_error_handler (struct nodepda_s*) ; 
 int /*<<< orphan*/  bte_recovery_timer ; 
 struct nodepda_s* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nodepda_s* nodepda ; 

__attribute__((used)) static void bte_recovery_timeout(struct timer_list *t)
{
	struct nodepda_s *nodepda = from_timer(nodepda, t, bte_recovery_timer);

	bte_error_handler(nodepda);
}