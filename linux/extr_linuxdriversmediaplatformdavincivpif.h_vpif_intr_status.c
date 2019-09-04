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
 int /*<<< orphan*/  VPIF_STATUS ; 
 int /*<<< orphan*/  VPIF_STATUS_CLR ; 
 int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vpif_intr_status(int channel)
{
	int status = 0;
	int mask;

	if (channel < 0 || channel > 3)
		return 0;

	mask = 1 << channel;
	status = regr(VPIF_STATUS) & mask;
	regw(status, VPIF_STATUS_CLR);

	return status;
}