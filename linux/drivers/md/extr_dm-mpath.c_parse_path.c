#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;
struct pgpath {TYPE_2__ path; int /*<<< orphan*/  activate_path; } ;
struct path_selector {TYPE_1__* type; } ;
struct multipath {scalar_t__ hw_handler_name; } ;
struct dm_target {char* error; int /*<<< orphan*/  table; struct multipath* private; } ;
struct dm_arg_set {int argc; int /*<<< orphan*/  argv; } ;
struct TYPE_7__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int (* add_path ) (struct path_selector*,TYPE_2__*,int,int /*<<< orphan*/ ,char**) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct pgpath* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activate_path_work ; 
 struct pgpath* alloc_pgpath () ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int dm_get_device (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,TYPE_3__*) ; 
 int /*<<< orphan*/  dm_shift_arg (struct dm_arg_set*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pgpath (struct pgpath*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* scsi_dh_attached_handler_name (struct request_queue*,int /*<<< orphan*/ ) ; 
 int setup_scsi_dh (int /*<<< orphan*/ ,struct multipath*,char const**,char**) ; 
 int stub1 (struct path_selector*,TYPE_2__*,int,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static struct pgpath *parse_path(struct dm_arg_set *as, struct path_selector *ps,
				 struct dm_target *ti)
{
	int r;
	struct pgpath *p;
	struct multipath *m = ti->private;
	struct request_queue *q;
	const char *attached_handler_name = NULL;

	/* we need at least a path arg */
	if (as->argc < 1) {
		ti->error = "no device given";
		return ERR_PTR(-EINVAL);
	}

	p = alloc_pgpath();
	if (!p)
		return ERR_PTR(-ENOMEM);

	r = dm_get_device(ti, dm_shift_arg(as), dm_table_get_mode(ti->table),
			  &p->path.dev);
	if (r) {
		ti->error = "error getting device";
		goto bad;
	}

	q = bdev_get_queue(p->path.dev->bdev);
	attached_handler_name = scsi_dh_attached_handler_name(q, GFP_KERNEL);
	if (attached_handler_name || m->hw_handler_name) {
		INIT_DELAYED_WORK(&p->activate_path, activate_path_work);
		r = setup_scsi_dh(p->path.dev->bdev, m, &attached_handler_name, &ti->error);
		kfree(attached_handler_name);
		if (r) {
			dm_put_device(ti, p->path.dev);
			goto bad;
		}
	}

	r = ps->type->add_path(ps, &p->path, as->argc, as->argv, &ti->error);
	if (r) {
		dm_put_device(ti, p->path.dev);
		goto bad;
	}

	return p;
 bad:
	free_pgpath(p);
	return ERR_PTR(r);
}