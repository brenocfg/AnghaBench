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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_is_ready (struct docg3*) ; 

__attribute__((used)) static int doc_wait_ready(struct docg3 *docg3)
{
	int maxWaitCycles = 100;

	do {
		doc_delay(docg3, 4);
		cpu_relax();
	} while (!doc_is_ready(docg3) && maxWaitCycles--);
	doc_delay(docg3, 2);
	if (maxWaitCycles > 0)
		return 0;
	else
		return -EIO;
}