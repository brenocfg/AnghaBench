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
struct s390_load_data {unsigned long initrd_load_addr; scalar_t__ kernel_buf; } ;
struct kimage {scalar_t__ cmdline_buf_len; scalar_t__ type; unsigned long initrd_buf_len; scalar_t__ initrd_buf; int /*<<< orphan*/  cmdline_buf; } ;
struct TYPE_2__ {unsigned long start; int end; } ;

/* Variables and functions */
 scalar_t__ ARCH_COMMAND_LINE_SIZE ; 
 scalar_t__ COMMAND_LINE_OFFSET ; 
 int /*<<< orphan*/  EINVAL ; 
 int* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ INITRD_SIZE_OFFSET ; 
 scalar_t__ INITRD_START_OFFSET ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 scalar_t__ OLDMEM_BASE_OFFSET ; 
 scalar_t__ OLDMEM_SIZE_OFFSET ; 
 TYPE_1__ crashk_res ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int *kexec_file_update_kernel(struct kimage *image,
			      struct s390_load_data *data)
{
	unsigned long *loc;

	if (image->cmdline_buf_len >= ARCH_COMMAND_LINE_SIZE)
		return ERR_PTR(-EINVAL);

	if (image->cmdline_buf_len)
		memcpy(data->kernel_buf + COMMAND_LINE_OFFSET,
		       image->cmdline_buf, image->cmdline_buf_len);

	if (image->type == KEXEC_TYPE_CRASH) {
		loc = (unsigned long *)(data->kernel_buf + OLDMEM_BASE_OFFSET);
		*loc = crashk_res.start;

		loc = (unsigned long *)(data->kernel_buf + OLDMEM_SIZE_OFFSET);
		*loc = crashk_res.end - crashk_res.start + 1;
	}

	if (image->initrd_buf) {
		loc = (unsigned long *)(data->kernel_buf + INITRD_START_OFFSET);
		*loc = data->initrd_load_addr;

		loc = (unsigned long *)(data->kernel_buf + INITRD_SIZE_OFFSET);
		*loc = image->initrd_buf_len;
	}

	return NULL;
}