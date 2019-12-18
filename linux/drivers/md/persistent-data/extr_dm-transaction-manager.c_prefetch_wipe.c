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
struct prefetch_set {int /*<<< orphan*/ * blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREFETCH_SENTINEL ; 
 unsigned int PREFETCH_SIZE ; 

__attribute__((used)) static void prefetch_wipe(struct prefetch_set *p)
{
	unsigned i;
	for (i = 0; i < PREFETCH_SIZE; i++)
		p->blocks[i] = PREFETCH_SENTINEL;
}