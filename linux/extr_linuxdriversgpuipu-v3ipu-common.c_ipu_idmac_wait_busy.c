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
struct ipuv3_channel {int /*<<< orphan*/  num; struct ipu_soc* ipu; } ;
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IDMAC_CHA_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int idma_mask (int /*<<< orphan*/ ) ; 
 int ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int ipu_idmac_wait_busy(struct ipuv3_channel *channel, int ms)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(ms);
	while (ipu_idmac_read(ipu, IDMAC_CHA_BUSY(channel->num)) &
			idma_mask(channel->num)) {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;
		cpu_relax();
	}

	return 0;
}