#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s390_load_data {char* kernel_buf; int /*<<< orphan*/  memsz; } ;
struct kimage {scalar_t__ type; } ;
struct kexec_buf {char* buffer; scalar_t__ memsz; int /*<<< orphan*/  mem; int /*<<< orphan*/  bufsz; struct kimage* image; } ;
struct TYPE_6__ {scalar_t__ start; } ;
struct TYPE_5__ {int e_phoff; int e_phnum; } ;
struct TYPE_4__ {scalar_t__ p_type; int p_offset; scalar_t__ p_paddr; scalar_t__ p_memsz; int /*<<< orphan*/  p_align; int /*<<< orphan*/  p_filesz; } ;
typedef  TYPE_1__ Elf_Phdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 scalar_t__ PT_LOAD ; 
 scalar_t__ STARTUP_NORMAL_OFFSET ; 
 TYPE_3__ crashk_res ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

__attribute__((used)) static int kexec_file_add_elf_kernel(struct kimage *image,
				     struct s390_load_data *data,
				     char *kernel, unsigned long kernel_len)
{
	struct kexec_buf buf;
	const Elf_Ehdr *ehdr;
	const Elf_Phdr *phdr;
	int i, ret;

	ehdr = (Elf_Ehdr *)kernel;
	buf.image = image;

	phdr = (void *)ehdr + ehdr->e_phoff;
	for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
		if (phdr->p_type != PT_LOAD)
			continue;

		buf.buffer = kernel + phdr->p_offset;
		buf.bufsz = phdr->p_filesz;

		buf.mem = ALIGN(phdr->p_paddr, phdr->p_align);
		buf.memsz = phdr->p_memsz;

		if (phdr->p_paddr == 0) {
			data->kernel_buf = buf.buffer;
			data->memsz += STARTUP_NORMAL_OFFSET;

			buf.buffer += STARTUP_NORMAL_OFFSET;
			buf.bufsz -= STARTUP_NORMAL_OFFSET;

			buf.mem += STARTUP_NORMAL_OFFSET;
			buf.memsz -= STARTUP_NORMAL_OFFSET;
		}

		if (image->type == KEXEC_TYPE_CRASH)
			buf.mem += crashk_res.start;

		ret = kexec_add_buffer(&buf);
		if (ret)
			return ret;

		data->memsz += buf.memsz;
	}

	return 0;
}