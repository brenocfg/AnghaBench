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
typedef  int u8 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int ARL_SRCH_STDN ; 
 int ARL_SRCH_VLID ; 
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARL_SRCH_CTL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int b53_arl_search_wait(struct b53_device *dev)
{
	unsigned int timeout = 1000;
	u8 reg;

	do {
		b53_read8(dev, B53_ARLIO_PAGE, B53_ARL_SRCH_CTL, &reg);
		if (!(reg & ARL_SRCH_STDN))
			return 0;

		if (reg & ARL_SRCH_VLID)
			return 0;

		usleep_range(1000, 2000);
	} while (timeout--);

	return -ETIMEDOUT;
}