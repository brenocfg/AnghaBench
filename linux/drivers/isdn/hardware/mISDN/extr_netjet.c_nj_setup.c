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
typedef  int /*<<< orphan*/  u32 ;
struct tiger_hw {int base; int base_s; int /*<<< orphan*/  isac; int /*<<< orphan*/  name; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  ISAC ; 
 int /*<<< orphan*/  nj ; 
 int pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nj_setup(struct tiger_hw *card)
{
	card->base = pci_resource_start(card->pdev, 0);
	card->base_s = pci_resource_len(card->pdev, 0);
	if (!request_region(card->base, card->base_s, card->name)) {
		pr_info("%s: NETjet config port %#x-%#x already in use\n",
			card->name, card->base,
			(u32)(card->base + card->base_s - 1));
		card->base_s = 0;
		return -EIO;
	}
	ASSIGN_FUNC(nj, ISAC, card->isac);
	return 0;
}