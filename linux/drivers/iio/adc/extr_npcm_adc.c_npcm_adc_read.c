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
typedef  int u32 ;
struct npcm_adc {int int_status; scalar_t__ regs; int /*<<< orphan*/  dev; scalar_t__ rst_regmap; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int NPCM7XX_IPSRST1_ADC_RST ; 
 int /*<<< orphan*/  NPCM7XX_IPSRST1_OFFSET ; 
 scalar_t__ NPCM_ADCCON ; 
 int NPCM_ADCCON_ADC_CONV ; 
 int NPCM_ADCCON_CH (int /*<<< orphan*/ ) ; 
 int NPCM_ADCCON_CH_MASK ; 
 scalar_t__ NPCM_ADCDATA ; 
 int NPCM_ADC_DATA_MASK (int) ; 
 int NPCM_ADC_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_adc_read(struct npcm_adc *info, int *val, u8 channel)
{
	int ret;
	u32 regtemp;

	/* Select ADC channel */
	regtemp = ioread32(info->regs + NPCM_ADCCON);
	regtemp &= ~NPCM_ADCCON_CH_MASK;
	info->int_status = false;
	iowrite32(regtemp | NPCM_ADCCON_CH(channel) |
		  NPCM_ADCCON_ADC_CONV, info->regs + NPCM_ADCCON);

	ret = wait_event_interruptible_timeout(info->wq, info->int_status,
					       msecs_to_jiffies(10));
	if (ret == 0) {
		regtemp = ioread32(info->regs + NPCM_ADCCON);
		if ((regtemp & NPCM_ADCCON_ADC_CONV) && info->rst_regmap) {
			/* if conversion failed - reset ADC module */
			regmap_write(info->rst_regmap, NPCM7XX_IPSRST1_OFFSET,
				     NPCM7XX_IPSRST1_ADC_RST);
			msleep(100);
			regmap_write(info->rst_regmap, NPCM7XX_IPSRST1_OFFSET,
				     0x0);
			msleep(100);

			/* Enable ADC and start conversion module */
			iowrite32(NPCM_ADC_ENABLE | NPCM_ADCCON_ADC_CONV,
				  info->regs + NPCM_ADCCON);
			dev_err(info->dev, "RESET ADC Complete\n");
		}
		return -ETIMEDOUT;
	}
	if (ret < 0)
		return ret;

	*val = NPCM_ADC_DATA_MASK(ioread32(info->regs + NPCM_ADCDATA));

	return 0;
}