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
struct sh_veu_file {int cfg_needed; struct sh_veu_dev* veu_dev; } ;
struct sh_veu_dev {int /*<<< orphan*/  dev; } ;
struct file {struct sh_veu_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct sh_veu_file*) ; 
 struct sh_veu_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct sh_veu_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_veu_open(struct file *file)
{
	struct sh_veu_dev *veu = video_drvdata(file);
	struct sh_veu_file *veu_file;

	veu_file = kzalloc(sizeof(*veu_file), GFP_KERNEL);
	if (!veu_file)
		return -ENOMEM;

	veu_file->veu_dev = veu;
	veu_file->cfg_needed = true;

	file->private_data = veu_file;

	pm_runtime_get_sync(veu->dev);

	dev_dbg(veu->dev, "Created instance %p\n", veu_file);

	return 0;
}