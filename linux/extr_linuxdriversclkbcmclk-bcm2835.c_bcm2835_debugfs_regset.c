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
typedef  scalar_t__ u32 ;
struct dentry {int dummy; } ;
struct debugfs_regset32 {size_t nregs; scalar_t__ base; struct debugfs_reg32* regs; } ;
struct debugfs_reg32 {int dummy; } ;
struct bcm2835_cprman {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_regset32 (char*,int /*<<< orphan*/ ,struct dentry*,struct debugfs_regset32*) ; 
 struct debugfs_regset32* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_debugfs_regset(struct bcm2835_cprman *cprman, u32 base,
				  struct debugfs_reg32 *regs, size_t nregs,
				  struct dentry *dentry)
{
	struct debugfs_regset32 *regset;

	regset = devm_kzalloc(cprman->dev, sizeof(*regset), GFP_KERNEL);
	if (!regset)
		return;

	regset->regs = regs;
	regset->nregs = nregs;
	regset->base = cprman->regs + base;

	debugfs_create_regset32("regdump", S_IRUGO, dentry, regset);
}