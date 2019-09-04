#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ interval; } ;
struct TYPE_3__ {scalar_t__ interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_pool ; 
 int /*<<< orphan*/  crng_global_init_time ; 
 int /*<<< orphan*/  crng_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_std_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_pool ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  primary_crng ; 
 scalar_t__ ratelimit_disable ; 
 TYPE_2__ unseeded_warning ; 
 TYPE_1__ urandom_warning ; 

__attribute__((used)) static int rand_initialize(void)
{
	init_std_data(&input_pool);
	init_std_data(&blocking_pool);
	crng_initialize(&primary_crng);
	crng_global_init_time = jiffies;
	if (ratelimit_disable) {
		urandom_warning.interval = 0;
		unseeded_warning.interval = 0;
	}
	return 0;
}