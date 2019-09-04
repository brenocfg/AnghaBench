#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct nouveau_drm {TYPE_2__ client; int /*<<< orphan*/  clients; } ;
struct TYPE_3__ {int super; } ;
struct nouveau_cli {int /*<<< orphan*/  head; TYPE_1__ base; } ;
struct drm_file {struct nouveau_cli* driver_priv; int /*<<< orphan*/  pid; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_comm (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nouveau_cli*) ; 
 struct nouveau_cli* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_cli_fini (struct nouveau_cli*) ; 
 int nouveau_cli_init (struct nouveau_drm*,char*,struct nouveau_cli*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int pid_nr (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
nouveau_drm_open(struct drm_device *dev, struct drm_file *fpriv)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_cli *cli;
	char name[32], tmpname[TASK_COMM_LEN];
	int ret;

	/* need to bring up power immediately if opening device */
	ret = pm_runtime_get_sync(dev->dev);
	if (ret < 0 && ret != -EACCES)
		return ret;

	get_task_comm(tmpname, current);
	snprintf(name, sizeof(name), "%s[%d]", tmpname, pid_nr(fpriv->pid));

	if (!(cli = kzalloc(sizeof(*cli), GFP_KERNEL))) {
		ret = -ENOMEM;
		goto done;
	}

	ret = nouveau_cli_init(drm, name, cli);
	if (ret)
		goto done;

	cli->base.super = false;

	fpriv->driver_priv = cli;

	mutex_lock(&drm->client.mutex);
	list_add(&cli->head, &drm->clients);
	mutex_unlock(&drm->client.mutex);

done:
	if (ret && cli) {
		nouveau_cli_fini(cli);
		kfree(cli);
	}

	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);
	return ret;
}