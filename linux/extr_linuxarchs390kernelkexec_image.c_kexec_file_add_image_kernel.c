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
struct s390_load_data {char* kernel_buf; int /*<<< orphan*/  memsz; } ;
struct kimage {scalar_t__ type; } ;
struct kexec_buf {char* buffer; int bufsz; int mem; int memsz; struct kimage* image; } ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int STARTUP_NORMAL_OFFSET ; 
 TYPE_1__ crashk_res ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

__attribute__((used)) static int kexec_file_add_image_kernel(struct kimage *image,
				       struct s390_load_data *data,
				       char *kernel, unsigned long kernel_len)
{
	struct kexec_buf buf;
	int ret;

	buf.image = image;

	buf.buffer = kernel + STARTUP_NORMAL_OFFSET;
	buf.bufsz = kernel_len - STARTUP_NORMAL_OFFSET;

	buf.mem = STARTUP_NORMAL_OFFSET;
	if (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	ret = kexec_add_buffer(&buf);

	data->kernel_buf = kernel;
	data->memsz += buf.memsz + STARTUP_NORMAL_OFFSET;

	return ret;
}