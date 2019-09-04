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
struct vtpm_proxy_new_dev {int flags; int fd; int /*<<< orphan*/  tpm_num; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct proxy_dev {int flags; TYPE_2__* chip; } ;
struct file {int flags; TYPE_2__* chip; } ;
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_num; TYPE_1__ dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct proxy_dev* ERR_CAST (struct proxy_dev*) ; 
 struct proxy_dev* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct proxy_dev*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PTR_ERR (struct proxy_dev*) ; 
 int /*<<< orphan*/  TPM_CHIP_FLAG_TPM2 ; 
 int VTPM_PROXY_FLAGS_ALL ; 
 int VTPM_PROXY_FLAG_TPM2 ; 
 struct proxy_dev* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct proxy_dev*,int /*<<< orphan*/ ) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 struct proxy_dev* vtpm_proxy_create_proxy_dev () ; 
 int /*<<< orphan*/  vtpm_proxy_delete_proxy_dev (struct proxy_dev*) ; 
 int /*<<< orphan*/  vtpm_proxy_fops ; 
 int /*<<< orphan*/  vtpm_proxy_fops_open (struct proxy_dev*) ; 
 int /*<<< orphan*/  vtpm_proxy_work_start (struct proxy_dev*) ; 

__attribute__((used)) static struct file *vtpm_proxy_create_device(
				 struct vtpm_proxy_new_dev *vtpm_new_dev)
{
	struct proxy_dev *proxy_dev;
	int rc, fd;
	struct file *file;

	if (vtpm_new_dev->flags & ~VTPM_PROXY_FLAGS_ALL)
		return ERR_PTR(-EOPNOTSUPP);

	proxy_dev = vtpm_proxy_create_proxy_dev();
	if (IS_ERR(proxy_dev))
		return ERR_CAST(proxy_dev);

	proxy_dev->flags = vtpm_new_dev->flags;

	/* setup an anonymous file for the server-side */
	fd = get_unused_fd_flags(O_RDWR);
	if (fd < 0) {
		rc = fd;
		goto err_delete_proxy_dev;
	}

	file = anon_inode_getfile("[vtpms]", &vtpm_proxy_fops, proxy_dev,
				  O_RDWR);
	if (IS_ERR(file)) {
		rc = PTR_ERR(file);
		goto err_put_unused_fd;
	}

	/* from now on we can unwind with put_unused_fd() + fput() */
	/* simulate an open() on the server side */
	vtpm_proxy_fops_open(file);

	if (proxy_dev->flags & VTPM_PROXY_FLAG_TPM2)
		proxy_dev->chip->flags |= TPM_CHIP_FLAG_TPM2;

	vtpm_proxy_work_start(proxy_dev);

	vtpm_new_dev->fd = fd;
	vtpm_new_dev->major = MAJOR(proxy_dev->chip->dev.devt);
	vtpm_new_dev->minor = MINOR(proxy_dev->chip->dev.devt);
	vtpm_new_dev->tpm_num = proxy_dev->chip->dev_num;

	return file;

err_put_unused_fd:
	put_unused_fd(fd);

err_delete_proxy_dev:
	vtpm_proxy_delete_proxy_dev(proxy_dev);

	return ERR_PTR(rc);
}