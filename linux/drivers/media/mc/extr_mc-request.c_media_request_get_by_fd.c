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
struct media_request {struct media_device* mdev; } ;
struct media_device {int /*<<< orphan*/  dev; TYPE_2__* ops; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_queue; int /*<<< orphan*/  req_validate; } ;
struct TYPE_3__ {struct media_request* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADR ; 
 int /*<<< orphan*/  EINVAL ; 
 struct media_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  media_request_get (struct media_request*) ; 
 int /*<<< orphan*/  request_fops ; 

struct media_request *
media_request_get_by_fd(struct media_device *mdev, int request_fd)
{
	struct fd f;
	struct media_request *req;

	if (!mdev || !mdev->ops ||
	    !mdev->ops->req_validate || !mdev->ops->req_queue)
		return ERR_PTR(-EBADR);

	f = fdget(request_fd);
	if (!f.file)
		goto err_no_req_fd;

	if (f.file->f_op != &request_fops)
		goto err_fput;
	req = f.file->private_data;
	if (req->mdev != mdev)
		goto err_fput;

	/*
	 * Note: as long as someone has an open filehandle of the request,
	 * the request can never be released. The fdget() above ensures that
	 * even if userspace closes the request filehandle, the release()
	 * fop won't be called, so the media_request_get() always succeeds
	 * and there is no race condition where the request was released
	 * before media_request_get() is called.
	 */
	media_request_get(req);
	fdput(f);

	return req;

err_fput:
	fdput(f);

err_no_req_fd:
	dev_dbg(mdev->dev, "cannot find request_fd %d\n", request_fd);
	return ERR_PTR(-EINVAL);
}