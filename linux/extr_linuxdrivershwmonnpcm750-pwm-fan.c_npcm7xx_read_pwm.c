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
typedef  int u32 ;
struct npcm7xx_pwm_fan_data {int /*<<< orphan*/  pwm_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE ; 
 int /*<<< orphan*/  NPCM7XX_PWM_REG_CMRx (int /*<<< orphan*/ ,int,int) ; 
 struct npcm7xx_pwm_fan_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_pwm_input 128 
 long ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm7xx_read_pwm(struct device *dev, u32 attr, int channel,
			    long *val)
{
	struct npcm7xx_pwm_fan_data *data = dev_get_drvdata(dev);
	u32 pmw_ch = (channel % NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);
	u32 module = (channel / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);

	switch (attr) {
	case hwmon_pwm_input:
		*val = ioread32
			(NPCM7XX_PWM_REG_CMRx(data->pwm_base, module, pmw_ch));
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}