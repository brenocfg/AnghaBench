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

/* Variables and functions */
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup_pow_of_two (unsigned long) ; 

__attribute__((used)) static unsigned long roundup_ring_size(unsigned long pending)
{
	return max(128ul, roundup_pow_of_two(pending+1));
}