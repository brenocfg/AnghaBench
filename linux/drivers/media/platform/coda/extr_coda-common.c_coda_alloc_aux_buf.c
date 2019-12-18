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
struct dentry {int dummy; } ;
struct coda_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {size_t size; scalar_t__ data; } ;
struct coda_aux_buf {size_t size; int /*<<< orphan*/  dentry; TYPE_1__ blob; scalar_t__ vaddr; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_blob (char const*,int,struct dentry*,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,char const*,size_t) ; 

int coda_alloc_aux_buf(struct coda_dev *dev, struct coda_aux_buf *buf,
		       size_t size, const char *name, struct dentry *parent)
{
	buf->vaddr = dma_alloc_coherent(dev->dev, size, &buf->paddr,
					GFP_KERNEL);
	if (!buf->vaddr) {
		v4l2_err(&dev->v4l2_dev,
			 "Failed to allocate %s buffer of size %zu\n",
			 name, size);
		return -ENOMEM;
	}

	buf->size = size;

	if (name && parent) {
		buf->blob.data = buf->vaddr;
		buf->blob.size = size;
		buf->dentry = debugfs_create_blob(name, 0644, parent,
						  &buf->blob);
		if (!buf->dentry)
			dev_warn(dev->dev,
				 "failed to create debugfs entry %s\n", name);
	}

	return 0;
}