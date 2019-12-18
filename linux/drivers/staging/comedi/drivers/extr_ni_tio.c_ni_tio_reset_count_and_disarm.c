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
struct ni_gpct {unsigned int counter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GI_RESET (unsigned int) ; 
 int /*<<< orphan*/  NITIO_RESET_REG (unsigned int) ; 
 int /*<<< orphan*/  ni_tio_write (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_tio_reset_count_and_disarm(struct ni_gpct *counter)
{
	unsigned int cidx = counter->counter_index;

	ni_tio_write(counter, GI_RESET(cidx), NITIO_RESET_REG(cidx));
}