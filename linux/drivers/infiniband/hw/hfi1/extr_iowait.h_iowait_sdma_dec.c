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
struct iowait {int /*<<< orphan*/  sdma_busy; } ;

/* Variables and functions */
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int iowait_sdma_dec(struct iowait *wait)
{
	if (!wait)
		return 0;
	return atomic_dec_and_test(&wait->sdma_busy);
}