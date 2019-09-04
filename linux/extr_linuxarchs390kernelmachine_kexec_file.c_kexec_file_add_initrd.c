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
struct s390_load_data {unsigned long memsz; unsigned long initrd_load_addr; } ;
struct kimage {scalar_t__ type; } ;
struct kexec_buf {char* buffer; unsigned long bufsz; unsigned long mem; unsigned long memsz; struct kimage* image; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__ crashk_res ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

int kexec_file_add_initrd(struct kimage *image, struct s390_load_data *data,
			  char *initrd, unsigned long initrd_len)
{
	struct kexec_buf buf;
	int ret;

	buf.image = image;

	buf.buffer = initrd;
	buf.bufsz = initrd_len;

	data->memsz = ALIGN(data->memsz, PAGE_SIZE);
	buf.mem = data->memsz;
	if (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	data->initrd_load_addr = buf.mem;
	data->memsz += buf.memsz;

	ret = kexec_add_buffer(&buf);
	return ret;
}