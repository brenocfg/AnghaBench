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
typedef  int u32 ;
struct threshold_block {int threshold_limit; int /*<<< orphan*/  address; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int THRESHOLD_MAX ; 
 int /*<<< orphan*/  rdmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_error_count(struct threshold_block *b, char *buf)
{
	u32 lo, hi;

	rdmsr_on_cpu(b->cpu, b->address, &lo, &hi);

	return sprintf(buf, "%u\n", ((hi & THRESHOLD_MAX) -
				     (THRESHOLD_MAX - b->threshold_limit)));
}