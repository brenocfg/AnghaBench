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
struct list_head {int dummy; } ;
struct coresight_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct list_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int _coresight_build_path (struct coresight_device*,struct coresight_device*,struct list_head*) ; 
 int /*<<< orphan*/  kfree (struct list_head*) ; 
 struct list_head* kzalloc (int,int /*<<< orphan*/ ) ; 

struct list_head *coresight_build_path(struct coresight_device *source,
				       struct coresight_device *sink)
{
	struct list_head *path;
	int rc;

	if (!sink)
		return ERR_PTR(-EINVAL);

	path = kzalloc(sizeof(struct list_head), GFP_KERNEL);
	if (!path)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(path);

	rc = _coresight_build_path(source, sink, path);
	if (rc) {
		kfree(path);
		return ERR_PTR(rc);
	}

	return path;
}