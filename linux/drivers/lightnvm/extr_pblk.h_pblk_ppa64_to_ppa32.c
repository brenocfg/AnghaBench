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
struct ppa_addr {int dummy; } ;
struct pblk {int /*<<< orphan*/  addrf; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvm_ppa64_to_ppa32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ppa_addr) ; 

__attribute__((used)) static inline u32 pblk_ppa64_to_ppa32(struct pblk *pblk, struct ppa_addr ppa64)
{
	struct nvm_tgt_dev *dev = pblk->dev;

	return nvm_ppa64_to_ppa32(dev->parent, &pblk->addrf, ppa64);
}