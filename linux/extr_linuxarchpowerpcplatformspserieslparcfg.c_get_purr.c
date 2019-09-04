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
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC64_INIT (int /*<<< orphan*/ ) ; 
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_get_purr ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long get_purr(void)
{
	atomic64_t purr = ATOMIC64_INIT(0);

	on_each_cpu(cpu_get_purr, &purr, 1);

	return atomic64_read(&purr);
}