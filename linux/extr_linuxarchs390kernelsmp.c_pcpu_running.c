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
struct pcpu {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ SIGP_CC_STATUS_STORED ; 
 int /*<<< orphan*/  SIGP_SENSE_RUNNING ; 
 scalar_t__ __pcpu_sigp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int pcpu_running(struct pcpu *pcpu)
{
	if (__pcpu_sigp(pcpu->address, SIGP_SENSE_RUNNING,
			0, NULL) != SIGP_CC_STATUS_STORED)
		return 1;
	/* Status stored condition code is equivalent to cpu not running. */
	return 0;
}