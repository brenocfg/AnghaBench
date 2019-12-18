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
struct vb2_queue {int io_modes; int num_buffers; struct vb2_fileio_data* fileio; int /*<<< orphan*/  type; TYPE_3__** bufs; int /*<<< orphan*/  fileio_write_immediately; int /*<<< orphan*/  fileio_read_once; scalar_t__ streaming; TYPE_1__* mem_ops; } ;
struct vb2_fileio_data {unsigned int count; int initial_index; int cur_index; int /*<<< orphan*/  memory; TYPE_2__* bufs; int /*<<< orphan*/  type; int /*<<< orphan*/  write_immediately; int /*<<< orphan*/  read_once; } ;
struct TYPE_7__ {int num_planes; } ;
struct TYPE_6__ {int queued; int /*<<< orphan*/  size; int /*<<< orphan*/ * vaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VB2_MEMORY_MMAP ; 
 int VB2_READ ; 
 int VB2_WRITE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dprintk (int,char*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vb2_fileio_data*) ; 
 struct vb2_fileio_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int vb2_core_qbuf (struct vb2_queue*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vb2_core_reqbufs (struct vb2_queue*,int /*<<< orphan*/ ,unsigned int*) ; 
 int vb2_core_streamon (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_size (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vb2_init_fileio(struct vb2_queue *q, int read)
{
	struct vb2_fileio_data *fileio;
	int i, ret;
	unsigned int count = 0;

	/*
	 * Sanity check
	 */
	if (WARN_ON((read && !(q->io_modes & VB2_READ)) ||
		    (!read && !(q->io_modes & VB2_WRITE))))
		return -EINVAL;

	/*
	 * Check if device supports mapping buffers to kernel virtual space.
	 */
	if (!q->mem_ops->vaddr)
		return -EBUSY;

	/*
	 * Check if streaming api has not been already activated.
	 */
	if (q->streaming || q->num_buffers > 0)
		return -EBUSY;

	/*
	 * Start with count 1, driver can increase it in queue_setup()
	 */
	count = 1;

	dprintk(3, "setting up file io: mode %s, count %d, read_once %d, write_immediately %d\n",
		(read) ? "read" : "write", count, q->fileio_read_once,
		q->fileio_write_immediately);

	fileio = kzalloc(sizeof(*fileio), GFP_KERNEL);
	if (fileio == NULL)
		return -ENOMEM;

	fileio->read_once = q->fileio_read_once;
	fileio->write_immediately = q->fileio_write_immediately;

	/*
	 * Request buffers and use MMAP type to force driver
	 * to allocate buffers by itself.
	 */
	fileio->count = count;
	fileio->memory = VB2_MEMORY_MMAP;
	fileio->type = q->type;
	q->fileio = fileio;
	ret = vb2_core_reqbufs(q, fileio->memory, &fileio->count);
	if (ret)
		goto err_kfree;

	/*
	 * Check if plane_count is correct
	 * (multiplane buffers are not supported).
	 */
	if (q->bufs[0]->num_planes != 1) {
		ret = -EBUSY;
		goto err_reqbufs;
	}

	/*
	 * Get kernel address of each buffer.
	 */
	for (i = 0; i < q->num_buffers; i++) {
		fileio->bufs[i].vaddr = vb2_plane_vaddr(q->bufs[i], 0);
		if (fileio->bufs[i].vaddr == NULL) {
			ret = -EINVAL;
			goto err_reqbufs;
		}
		fileio->bufs[i].size = vb2_plane_size(q->bufs[i], 0);
	}

	/*
	 * Read mode requires pre queuing of all buffers.
	 */
	if (read) {
		/*
		 * Queue all buffers.
		 */
		for (i = 0; i < q->num_buffers; i++) {
			ret = vb2_core_qbuf(q, i, NULL, NULL);
			if (ret)
				goto err_reqbufs;
			fileio->bufs[i].queued = 1;
		}
		/*
		 * All buffers have been queued, so mark that by setting
		 * initial_index to q->num_buffers
		 */
		fileio->initial_index = q->num_buffers;
		fileio->cur_index = q->num_buffers;
	}

	/*
	 * Start streaming.
	 */
	ret = vb2_core_streamon(q, q->type);
	if (ret)
		goto err_reqbufs;

	return ret;

err_reqbufs:
	fileio->count = 0;
	vb2_core_reqbufs(q, fileio->memory, &fileio->count);

err_kfree:
	q->fileio = NULL;
	kfree(fileio);
	return ret;
}