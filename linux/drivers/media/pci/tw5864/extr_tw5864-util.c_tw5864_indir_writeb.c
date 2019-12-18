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
typedef  int u8 ;
typedef  int u16 ;
struct tw5864_dev {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int TW5864_ENABLE ; 
 int /*<<< orphan*/  TW5864_IND_CTL ; 
 int /*<<< orphan*/  TW5864_IND_DATA ; 
 int TW5864_RW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int tw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

void tw5864_indir_writeb(struct tw5864_dev *dev, u16 addr, u8 data)
{
	int retries = 30000;

	while (tw_readl(TW5864_IND_CTL) & BIT(31) && --retries)
		;
	if (!retries)
		dev_err(&dev->pci->dev,
			"tw_indir_writel() retries exhausted before writing\n");

	tw_writel(TW5864_IND_DATA, data);
	tw_writel(TW5864_IND_CTL, addr << 2 | TW5864_RW | TW5864_ENABLE);
}