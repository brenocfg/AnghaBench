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
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  IPU_MEM_RST ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int ipu_cm_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int ipu_memory_reset(struct ipu_soc *ipu)
{
	unsigned long timeout;

	ipu_cm_write(ipu, 0x807FFFFF, IPU_MEM_RST);

	timeout = jiffies + msecs_to_jiffies(1000);
	while (ipu_cm_read(ipu, IPU_MEM_RST) & 0x80000000) {
		if (time_after(jiffies, timeout))
			return -ETIME;
		cpu_relax();
	}

	return 0;
}