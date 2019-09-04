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
struct kimage {int nr_segments; TYPE_1__* segment; } ;
struct fdt_header {int dummy; } ;
typedef  int /*<<< orphan*/  fdt ;
struct TYPE_2__ {int memsz; scalar_t__ mem; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ copy_from_user (struct fdt_header*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fdt_check_header (struct fdt_header*) ; 
 int* kexec_args ; 
 scalar_t__ phys_to_virt (unsigned long) ; 

__attribute__((used)) static int generic_kexec_prepare(struct kimage *image)
{
	int i;

	for (i = 0; i < image->nr_segments; i++) {
		struct fdt_header fdt;

		if (image->segment[i].memsz <= sizeof(fdt))
			continue;

		if (copy_from_user(&fdt, image->segment[i].buf, sizeof(fdt)))
			continue;

		if (fdt_check_header(&fdt))
			continue;

		kexec_args[0] = -2;
		kexec_args[1] = (unsigned long)
			phys_to_virt((unsigned long)image->segment[i].mem);
		break;
	}
	return 0;
}