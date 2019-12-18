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
struct musb {int /*<<< orphan*/  ctrl_base; int /*<<< orphan*/  controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; } ;
struct dsps_glue {TYPE_1__ regset; struct dentry* dbgfs_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_regset32 (char*,int /*<<< orphan*/ ,struct dentry*,TYPE_1__*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsps_musb_regs ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int dsps_musb_dbg_init(struct musb *musb, struct dsps_glue *glue)
{
	struct dentry *root;
	char buf[128];

	sprintf(buf, "%s.dsps", dev_name(musb->controller));
	root = debugfs_create_dir(buf, NULL);
	glue->dbgfs_root = root;

	glue->regset.regs = dsps_musb_regs;
	glue->regset.nregs = ARRAY_SIZE(dsps_musb_regs);
	glue->regset.base = musb->ctrl_base;

	debugfs_create_regset32("regdump", S_IRUGO, root, &glue->regset);
	return 0;
}