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
struct ionic_lif {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long jiffies ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int ionic_wait_for_bit(struct ionic_lif *lif, int bitname)
{
	unsigned long tlimit = jiffies + HZ;

	while (test_and_set_bit(bitname, lif->state) &&
	       time_before(jiffies, tlimit))
		usleep_range(100, 200);

	return test_bit(bitname, lif->state);
}