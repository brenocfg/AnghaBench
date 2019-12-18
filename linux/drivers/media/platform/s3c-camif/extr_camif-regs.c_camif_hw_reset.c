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
struct camif_dev {TYPE_1__* variant; } ;
struct TYPE_2__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIGCTRL_IRQ_LEVEL ; 
 int /*<<< orphan*/  CIGCTRL_SWRST ; 
 int /*<<< orphan*/  CISRCFMT_ITU601_8BIT ; 
 scalar_t__ S3C6410_CAMIF_IP_REV ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIGCTRL ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CISRCFMT ; 
 int /*<<< orphan*/  camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void camif_hw_reset(struct camif_dev *camif)
{
	u32 cfg;

	cfg = camif_read(camif, S3C_CAMIF_REG_CISRCFMT);
	cfg |= CISRCFMT_ITU601_8BIT;
	camif_write(camif, S3C_CAMIF_REG_CISRCFMT, cfg);

	/* S/W reset */
	cfg = camif_read(camif, S3C_CAMIF_REG_CIGCTRL);
	cfg |= CIGCTRL_SWRST;
	if (camif->variant->ip_revision == S3C6410_CAMIF_IP_REV)
		cfg |= CIGCTRL_IRQ_LEVEL;
	camif_write(camif, S3C_CAMIF_REG_CIGCTRL, cfg);
	udelay(10);

	cfg = camif_read(camif, S3C_CAMIF_REG_CIGCTRL);
	cfg &= ~CIGCTRL_SWRST;
	camif_write(camif, S3C_CAMIF_REG_CIGCTRL, cfg);
	udelay(10);
}