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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pcpu {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int SIGP_CC_BUSY ; 
 int __pcpu_sigp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcpu_sigp_retry(struct pcpu *pcpu, u8 order, u32 parm)
{
	int cc, retry;

	for (retry = 0; ; retry++) {
		cc = __pcpu_sigp(pcpu->address, order, parm, NULL);
		if (cc != SIGP_CC_BUSY)
			break;
		if (retry >= 3)
			udelay(10);
	}
	return cc;
}