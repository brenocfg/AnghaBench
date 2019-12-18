#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct inode {scalar_t__ i_private; } ;
struct file {TYPE_1__* private_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_len; void* buffer; } ;
typedef  TYPE_1__ fnic_dbgfs_t ;
struct TYPE_8__ {scalar_t__ fnic_trace; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 TYPE_6__* fc_trc_flag ; 
 int /*<<< orphan*/  fnic_fc_trace_get_data (TYPE_1__*,scalar_t__) ; 
 int fnic_fc_trace_max_pages ; 
 int /*<<< orphan*/  fnic_get_trace_data (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int trace_max_pages ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fnic_trace_debugfs_open(struct inode *inode,
				  struct file *file)
{
	fnic_dbgfs_t *fnic_dbg_prt;
	u8 *rdata_ptr;
	rdata_ptr = (u8 *)inode->i_private;
	fnic_dbg_prt = kzalloc(sizeof(fnic_dbgfs_t), GFP_KERNEL);
	if (!fnic_dbg_prt)
		return -ENOMEM;

	if (*rdata_ptr == fc_trc_flag->fnic_trace) {
		fnic_dbg_prt->buffer = vmalloc(array3_size(3, trace_max_pages,
							   PAGE_SIZE));
		if (!fnic_dbg_prt->buffer) {
			kfree(fnic_dbg_prt);
			return -ENOMEM;
		}
		memset((void *)fnic_dbg_prt->buffer, 0,
		3 * (trace_max_pages * PAGE_SIZE));
		fnic_dbg_prt->buffer_len = fnic_get_trace_data(fnic_dbg_prt);
	} else {
		fnic_dbg_prt->buffer =
			vmalloc(array3_size(3, fnic_fc_trace_max_pages,
					    PAGE_SIZE));
		if (!fnic_dbg_prt->buffer) {
			kfree(fnic_dbg_prt);
			return -ENOMEM;
		}
		memset((void *)fnic_dbg_prt->buffer, 0,
			3 * (fnic_fc_trace_max_pages * PAGE_SIZE));
		fnic_dbg_prt->buffer_len =
			fnic_fc_trace_get_data(fnic_dbg_prt, *rdata_ptr);
	}
	file->private_data = fnic_dbg_prt;

	return 0;
}