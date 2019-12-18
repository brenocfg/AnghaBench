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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device* dev; } ;
struct stm32_romem_priv {TYPE_1__ cfg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STM32_SMC_PROG_OTP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int stm32_bsec_smc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_bsec_write(void *context, unsigned int offset, void *buf,
			    size_t bytes)
{
	struct stm32_romem_priv *priv = context;
	struct device *dev = priv->cfg.dev;
	u32 *buf32 = buf;
	int ret, i;

	/* Allow only writing complete 32-bits aligned words */
	if ((bytes % 4) || (offset % 4))
		return -EINVAL;

	for (i = offset; i < offset + bytes; i += 4) {
		ret = stm32_bsec_smc(STM32_SMC_PROG_OTP, i >> 2, *buf32++,
				     NULL);
		if (ret) {
			dev_err(dev, "Can't write data%d (%d)\n", i >> 2, ret);
			return ret;
		}
	}

	return 0;
}