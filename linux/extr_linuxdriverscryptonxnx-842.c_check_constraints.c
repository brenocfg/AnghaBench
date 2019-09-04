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
struct nx842_constraints {scalar_t__ maximum; } ;

/* Variables and functions */
 scalar_t__ BOUNCE_BUFFER_SIZE ; 

__attribute__((used)) static void check_constraints(struct nx842_constraints *c)
{
	/* limit maximum, to always have enough bounce buffer to decompress */
	if (c->maximum > BOUNCE_BUFFER_SIZE)
		c->maximum = BOUNCE_BUFFER_SIZE;
}