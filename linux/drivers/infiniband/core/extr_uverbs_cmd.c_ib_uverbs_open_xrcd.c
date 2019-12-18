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
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; TYPE_1__* ufile; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; struct ib_xrcd* object; } ;
struct ib_xrcd {TYPE_3__ uobject; int /*<<< orphan*/  usecnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  tgt_qp_list; int /*<<< orphan*/  tgt_qp_mutex; struct ib_device* device; struct inode* inode; } ;
struct ib_uxrcd_object {TYPE_3__ uobject; int /*<<< orphan*/  usecnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  tgt_qp_list; int /*<<< orphan*/  tgt_qp_mutex; struct ib_device* device; struct inode* inode; } ;
struct ib_uverbs_open_xrcd_resp {int /*<<< orphan*/  xrcd_handle; } ;
struct ib_uverbs_open_xrcd {int fd; int oflags; } ;
struct ib_uverbs_device {int /*<<< orphan*/  xrcd_tree_mutex; } ;
struct TYPE_6__ {struct ib_xrcd* (* alloc_xrcd ) (struct ib_device*,int /*<<< orphan*/ *) ;} ;
struct ib_device {TYPE_2__ ops; } ;
struct fd {scalar_t__ file; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {struct ib_uverbs_device* device; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct ib_xrcd*) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int PTR_ERR (struct ib_xrcd*) ; 
 int /*<<< orphan*/  UVERBS_OBJECT_XRCD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 struct inode* file_inode (scalar_t__) ; 
 struct ib_xrcd* find_xrcd (struct ib_uverbs_device*,struct inode*) ; 
 int /*<<< orphan*/  ib_dealloc_xrcd (struct ib_xrcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_uverbs_open_xrcd_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ib_xrcd* stub1 (struct ib_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ uobj_alloc (int /*<<< orphan*/ ,struct uverbs_attr_bundle*,struct ib_device**) ; 
 int /*<<< orphan*/  uobj_alloc_abort (TYPE_3__*,struct uverbs_attr_bundle*) ; 
 int uobj_alloc_commit (TYPE_3__*,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uverbs_get_cleared_udata (struct uverbs_attr_bundle*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_open_xrcd*,int) ; 
 int uverbs_response (struct uverbs_attr_bundle*,struct ib_uverbs_open_xrcd_resp*,int) ; 
 int /*<<< orphan*/  xrcd_table_delete (struct ib_uverbs_device*,struct inode*) ; 
 int xrcd_table_insert (struct ib_uverbs_device*,struct inode*,struct ib_xrcd*) ; 

__attribute__((used)) static int ib_uverbs_open_xrcd(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_device *ibudev = attrs->ufile->device;
	struct ib_uverbs_open_xrcd	cmd;
	struct ib_uverbs_open_xrcd_resp	resp;
	struct ib_uxrcd_object         *obj;
	struct ib_xrcd                 *xrcd = NULL;
	struct fd			f = {NULL, 0};
	struct inode                   *inode = NULL;
	int				ret = 0;
	int				new_xrcd = 0;
	struct ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	mutex_lock(&ibudev->xrcd_tree_mutex);

	if (cmd.fd != -1) {
		/* search for file descriptor */
		f = fdget(cmd.fd);
		if (!f.file) {
			ret = -EBADF;
			goto err_tree_mutex_unlock;
		}

		inode = file_inode(f.file);
		xrcd = find_xrcd(ibudev, inode);
		if (!xrcd && !(cmd.oflags & O_CREAT)) {
			/* no file descriptor. Need CREATE flag */
			ret = -EAGAIN;
			goto err_tree_mutex_unlock;
		}

		if (xrcd && cmd.oflags & O_EXCL) {
			ret = -EINVAL;
			goto err_tree_mutex_unlock;
		}
	}

	obj = (struct ib_uxrcd_object *)uobj_alloc(UVERBS_OBJECT_XRCD, attrs,
						   &ib_dev);
	if (IS_ERR(obj)) {
		ret = PTR_ERR(obj);
		goto err_tree_mutex_unlock;
	}

	if (!xrcd) {
		xrcd = ib_dev->ops.alloc_xrcd(ib_dev, &attrs->driver_udata);
		if (IS_ERR(xrcd)) {
			ret = PTR_ERR(xrcd);
			goto err;
		}

		xrcd->inode   = inode;
		xrcd->device  = ib_dev;
		atomic_set(&xrcd->usecnt, 0);
		mutex_init(&xrcd->tgt_qp_mutex);
		INIT_LIST_HEAD(&xrcd->tgt_qp_list);
		new_xrcd = 1;
	}

	atomic_set(&obj->refcnt, 0);
	obj->uobject.object = xrcd;
	memset(&resp, 0, sizeof resp);
	resp.xrcd_handle = obj->uobject.id;

	if (inode) {
		if (new_xrcd) {
			/* create new inode/xrcd table entry */
			ret = xrcd_table_insert(ibudev, inode, xrcd);
			if (ret)
				goto err_dealloc_xrcd;
		}
		atomic_inc(&xrcd->usecnt);
	}

	ret = uverbs_response(attrs, &resp, sizeof(resp));
	if (ret)
		goto err_copy;

	if (f.file)
		fdput(f);

	mutex_unlock(&ibudev->xrcd_tree_mutex);

	return uobj_alloc_commit(&obj->uobject, attrs);

err_copy:
	if (inode) {
		if (new_xrcd)
			xrcd_table_delete(ibudev, inode);
		atomic_dec(&xrcd->usecnt);
	}

err_dealloc_xrcd:
	ib_dealloc_xrcd(xrcd, uverbs_get_cleared_udata(attrs));

err:
	uobj_alloc_abort(&obj->uobject, attrs);

err_tree_mutex_unlock:
	if (f.file)
		fdput(f);

	mutex_unlock(&ibudev->xrcd_tree_mutex);

	return ret;
}