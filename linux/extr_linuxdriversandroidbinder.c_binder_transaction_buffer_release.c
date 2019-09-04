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
typedef  int const u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct flat_binder_object {int /*<<< orphan*/  handle; scalar_t__ binder; } ;
struct binder_ref_data {int /*<<< orphan*/  desc; int /*<<< orphan*/  debug_id; } ;
struct binder_proc {int /*<<< orphan*/  alloc; int /*<<< orphan*/  pid; } ;
struct binder_object_header {int type; } ;
struct binder_node {scalar_t__ ptr; int /*<<< orphan*/  debug_id; } ;
struct binder_fd_object {int /*<<< orphan*/  fd; } ;
struct binder_fd_array_object {int num_fds; int parent_offset; int /*<<< orphan*/  parent; } ;
struct binder_buffer_object {uintptr_t buffer; int length; } ;
struct binder_buffer {int debug_id; int offsets_size; int data; int /*<<< orphan*/  data_size; struct binder_node* target_node; } ;
typedef  int binder_size_t ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BINDER_DEBUG_TRANSACTION ; 
#define  BINDER_TYPE_BINDER 134 
#define  BINDER_TYPE_FD 133 
#define  BINDER_TYPE_FDA 132 
#define  BINDER_TYPE_HANDLE 131 
#define  BINDER_TYPE_PTR 130 
#define  BINDER_TYPE_WEAK_BINDER 129 
#define  BINDER_TYPE_WEAK_HANDLE 128 
 int SIZE_MAX ; 
 uintptr_t binder_alloc_get_user_buffer_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  binder_dec_node (struct binder_node*,int,int /*<<< orphan*/ ) ; 
 int binder_dec_ref_for_handle (struct binder_proc*,int /*<<< orphan*/ ,int,struct binder_ref_data*) ; 
 struct binder_node* binder_get_node (struct binder_proc*,scalar_t__) ; 
 int /*<<< orphan*/  binder_put_node (struct binder_node*) ; 
 size_t binder_validate_object (struct binder_buffer*,int) ; 
 struct binder_buffer_object* binder_validate_ptr (struct binder_buffer*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  task_close_fd (struct binder_proc*,int /*<<< orphan*/ ) ; 
 struct binder_fd_array_object* to_binder_fd_array_object (struct binder_object_header*) ; 
 struct binder_fd_object* to_binder_fd_object (struct binder_object_header*) ; 
 struct flat_binder_object* to_flat_binder_object (struct binder_object_header*) ; 

__attribute__((used)) static void binder_transaction_buffer_release(struct binder_proc *proc,
					      struct binder_buffer *buffer,
					      binder_size_t *failed_at)
{
	binder_size_t *offp, *off_start, *off_end;
	int debug_id = buffer->debug_id;

	binder_debug(BINDER_DEBUG_TRANSACTION,
		     "%d buffer release %d, size %zd-%zd, failed at %pK\n",
		     proc->pid, buffer->debug_id,
		     buffer->data_size, buffer->offsets_size, failed_at);

	if (buffer->target_node)
		binder_dec_node(buffer->target_node, 1, 0);

	off_start = (binder_size_t *)(buffer->data +
				      ALIGN(buffer->data_size, sizeof(void *)));
	if (failed_at)
		off_end = failed_at;
	else
		off_end = (void *)off_start + buffer->offsets_size;
	for (offp = off_start; offp < off_end; offp++) {
		struct binder_object_header *hdr;
		size_t object_size = binder_validate_object(buffer, *offp);

		if (object_size == 0) {
			pr_err("transaction release %d bad object at offset %lld, size %zd\n",
			       debug_id, (u64)*offp, buffer->data_size);
			continue;
		}
		hdr = (struct binder_object_header *)(buffer->data + *offp);
		switch (hdr->type) {
		case BINDER_TYPE_BINDER:
		case BINDER_TYPE_WEAK_BINDER: {
			struct flat_binder_object *fp;
			struct binder_node *node;

			fp = to_flat_binder_object(hdr);
			node = binder_get_node(proc, fp->binder);
			if (node == NULL) {
				pr_err("transaction release %d bad node %016llx\n",
				       debug_id, (u64)fp->binder);
				break;
			}
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        node %d u%016llx\n",
				     node->debug_id, (u64)node->ptr);
			binder_dec_node(node, hdr->type == BINDER_TYPE_BINDER,
					0);
			binder_put_node(node);
		} break;
		case BINDER_TYPE_HANDLE:
		case BINDER_TYPE_WEAK_HANDLE: {
			struct flat_binder_object *fp;
			struct binder_ref_data rdata;
			int ret;

			fp = to_flat_binder_object(hdr);
			ret = binder_dec_ref_for_handle(proc, fp->handle,
				hdr->type == BINDER_TYPE_HANDLE, &rdata);

			if (ret) {
				pr_err("transaction release %d bad handle %d, ret = %d\n",
				 debug_id, fp->handle, ret);
				break;
			}
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        ref %d desc %d\n",
				     rdata.debug_id, rdata.desc);
		} break;

		case BINDER_TYPE_FD: {
			struct binder_fd_object *fp = to_binder_fd_object(hdr);

			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        fd %d\n", fp->fd);
			if (failed_at)
				task_close_fd(proc, fp->fd);
		} break;
		case BINDER_TYPE_PTR:
			/*
			 * Nothing to do here, this will get cleaned up when the
			 * transaction buffer gets freed
			 */
			break;
		case BINDER_TYPE_FDA: {
			struct binder_fd_array_object *fda;
			struct binder_buffer_object *parent;
			uintptr_t parent_buffer;
			u32 *fd_array;
			size_t fd_index;
			binder_size_t fd_buf_size;

			fda = to_binder_fd_array_object(hdr);
			parent = binder_validate_ptr(buffer, fda->parent,
						     off_start,
						     offp - off_start);
			if (!parent) {
				pr_err("transaction release %d bad parent offset\n",
				       debug_id);
				continue;
			}
			/*
			 * Since the parent was already fixed up, convert it
			 * back to kernel address space to access it
			 */
			parent_buffer = parent->buffer -
				binder_alloc_get_user_buffer_offset(
						&proc->alloc);

			fd_buf_size = sizeof(u32) * fda->num_fds;
			if (fda->num_fds >= SIZE_MAX / sizeof(u32)) {
				pr_err("transaction release %d invalid number of fds (%lld)\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			if (fd_buf_size > parent->length ||
			    fda->parent_offset > parent->length - fd_buf_size) {
				/* No space for all file descriptors here. */
				pr_err("transaction release %d not enough space for %lld fds in buffer\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			fd_array = (u32 *)(parent_buffer + (uintptr_t)fda->parent_offset);
			for (fd_index = 0; fd_index < fda->num_fds; fd_index++)
				task_close_fd(proc, fd_array[fd_index]);
		} break;
		default:
			pr_err("transaction release %d bad object type %x\n",
				debug_id, hdr->type);
			break;
		}
	}
}