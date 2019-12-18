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
struct media_request {int /*<<< orphan*/  debug_str; scalar_t__ access_count; scalar_t__ updating_count; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  objects; int /*<<< orphan*/  kref; scalar_t__ num_incomplete_objects; int /*<<< orphan*/  state; struct media_device* mdev; } ;
struct media_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  request_id; TYPE_1__* ops; } ;
struct file {struct media_request* private_data; } ;
struct TYPE_2__ {struct media_request* (* req_alloc ) (struct media_device*) ;int /*<<< orphan*/  req_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  MEDIA_REQUEST_STATE_IDLE ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct media_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  request_fops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct media_request* stub1 (struct media_device*) ; 

int media_request_alloc(struct media_device *mdev, int *alloc_fd)
{
	struct media_request *req;
	struct file *filp;
	int fd;
	int ret;

	/* Either both are NULL or both are non-NULL */
	if (WARN_ON(!mdev->ops->req_alloc ^ !mdev->ops->req_free))
		return -ENOMEM;

	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0)
		return fd;

	filp = anon_inode_getfile("request", &request_fops, NULL, O_CLOEXEC);
	if (IS_ERR(filp)) {
		ret = PTR_ERR(filp);
		goto err_put_fd;
	}

	if (mdev->ops->req_alloc)
		req = mdev->ops->req_alloc(mdev);
	else
		req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req) {
		ret = -ENOMEM;
		goto err_fput;
	}

	filp->private_data = req;
	req->mdev = mdev;
	req->state = MEDIA_REQUEST_STATE_IDLE;
	req->num_incomplete_objects = 0;
	kref_init(&req->kref);
	INIT_LIST_HEAD(&req->objects);
	spin_lock_init(&req->lock);
	init_waitqueue_head(&req->poll_wait);
	req->updating_count = 0;
	req->access_count = 0;

	*alloc_fd = fd;

	snprintf(req->debug_str, sizeof(req->debug_str), "%u:%d",
		 atomic_inc_return(&mdev->request_id), fd);
	dev_dbg(mdev->dev, "request: allocated %s\n", req->debug_str);

	fd_install(fd, filp);

	return 0;

err_fput:
	fput(filp);

err_put_fd:
	put_unused_fd(fd);

	return ret;
}