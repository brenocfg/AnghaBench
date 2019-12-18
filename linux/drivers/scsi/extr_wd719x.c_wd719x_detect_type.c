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
struct wd719x {TYPE_1__* pdev; } ;
typedef  enum wd719x_card_type { ____Placeholder_wd719x_card_type } wd719x_card_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WD719X_GPIO_ID_BITS ; 
 int /*<<< orphan*/  WD719X_PCI_GPIO_CONTROL ; 
 int /*<<< orphan*/  WD719X_PCI_GPIO_DATA ; 
 int WD719X_TYPE_7193 ; 
 int WD719X_TYPE_7197 ; 
 int WD719X_TYPE_7296 ; 
 int WD719X_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int wd719x_readb (struct wd719x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd719x_writeb (struct wd719x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum wd719x_card_type wd719x_detect_type(struct wd719x *wd)
{
	u8 card = wd719x_readb(wd, WD719X_PCI_GPIO_CONTROL);

	card |= WD719X_GPIO_ID_BITS;
	wd719x_writeb(wd, WD719X_PCI_GPIO_CONTROL, card);
	card = wd719x_readb(wd, WD719X_PCI_GPIO_DATA) & WD719X_GPIO_ID_BITS;
	switch (card) {
	case 0x08:
		return WD719X_TYPE_7193;
	case 0x02:
		return WD719X_TYPE_7197;
	case 0x00:
		return WD719X_TYPE_7296;
	default:
		dev_warn(&wd->pdev->dev, "unknown card type 0x%x\n", card);
		return WD719X_TYPE_UNKNOWN;
	}
}