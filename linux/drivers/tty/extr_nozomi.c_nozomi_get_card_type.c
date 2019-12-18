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
typedef  int u32 ;
struct nozomi {int /*<<< orphan*/  card_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  F32_2 ; 
 int /*<<< orphan*/  F32_8 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (TYPE_1__*,int) ; 

__attribute__((used)) static void nozomi_get_card_type(struct nozomi *dc)
{
	int i;
	u32 size = 0;

	for (i = 0; i < 6; i++)
		size += pci_resource_len(dc->pdev, i);

	/* Assume card type F32_8 if no match */
	dc->card_type = size == 2048 ? F32_2 : F32_8;

	dev_info(&dc->pdev->dev, "Card type is: %d\n", dc->card_type);
}