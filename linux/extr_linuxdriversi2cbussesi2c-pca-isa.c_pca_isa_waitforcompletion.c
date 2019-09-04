#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_PCA_CON ; 
 int I2C_PCA_CON_SI ; 
 int irq ; 
 unsigned long jiffies ; 
 TYPE_1__ pca_isa_ops ; 
 int pca_isa_readbyte (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pca_wait ; 
 long time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int pca_isa_waitforcompletion(void *pd)
{
	unsigned long timeout;
	long ret;

	if (irq > -1) {
		ret = wait_event_timeout(pca_wait,
				pca_isa_readbyte(pd, I2C_PCA_CON)
				& I2C_PCA_CON_SI, pca_isa_ops.timeout);
	} else {
		/* Do polling */
		timeout = jiffies + pca_isa_ops.timeout;
		do {
			ret = time_before(jiffies, timeout);
			if (pca_isa_readbyte(pd, I2C_PCA_CON)
					& I2C_PCA_CON_SI)
				break;
			udelay(100);
		} while (ret);
	}

	return ret > 0;
}