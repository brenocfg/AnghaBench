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
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISREG_CCSR ; 
 int /*<<< orphan*/  CISREG_COR ; 
 int COR_SOFT_RESET ; 
 int ENODEV ; 
 int HCR_IDLE ; 
 int HCR_MEM16 ; 
 int HCR_RUN ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int pcmcia_read_config_byte (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int pcmcia_write_config_byte (struct pcmcia_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
spectrum_reset(struct pcmcia_device *link, int idle)
{
	int ret;
	u8 save_cor;
	u8 ccsr;

	/* Doing it if hardware is gone is guaranteed crash */
	if (!pcmcia_dev_present(link))
		return -ENODEV;

	/* Save original COR value */
	ret = pcmcia_read_config_byte(link, CISREG_COR, &save_cor);
	if (ret)
		goto failed;

	/* Soft-Reset card */
	ret = pcmcia_write_config_byte(link, CISREG_COR,
				(save_cor | COR_SOFT_RESET));
	if (ret)
		goto failed;
	udelay(1000);

	/* Read CCSR */
	ret = pcmcia_read_config_byte(link, CISREG_CCSR, &ccsr);
	if (ret)
		goto failed;

	/*
	 * Start or stop the firmware.  Memory width bit should be
	 * preserved from the value we've just read.
	 */
	ccsr = (idle ? HCR_IDLE : HCR_RUN) | (ccsr & HCR_MEM16);
	ret = pcmcia_write_config_byte(link, CISREG_CCSR, ccsr);
	if (ret)
		goto failed;
	udelay(1000);

	/* Restore original COR configuration index */
	ret = pcmcia_write_config_byte(link, CISREG_COR,
				(save_cor & ~COR_SOFT_RESET));
	if (ret)
		goto failed;
	udelay(1000);
	return 0;

failed:
	return -ENODEV;
}