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
struct clone {int /*<<< orphan*/  hydration_batch_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_hydration_batch_size(struct clone *clone, unsigned int nr_regions)
{
	WRITE_ONCE(clone->hydration_batch_size, nr_regions);
}