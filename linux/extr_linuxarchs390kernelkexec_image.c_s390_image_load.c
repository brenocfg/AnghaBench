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
struct s390_load_data {int /*<<< orphan*/  member_0; } ;
struct kimage {int dummy; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 int kexec_file_add_image_kernel (struct kimage*,struct s390_load_data*,char*,unsigned long) ; 
 int kexec_file_add_initrd (struct kimage*,struct s390_load_data*,char*,unsigned long) ; 
 int kexec_file_add_purgatory (struct kimage*,struct s390_load_data*) ; 
 void* kexec_file_update_kernel (struct kimage*,struct s390_load_data*) ; 

__attribute__((used)) static void *s390_image_load(struct kimage *image,
			     char *kernel, unsigned long kernel_len,
			     char *initrd, unsigned long initrd_len,
			     char *cmdline, unsigned long cmdline_len)
{
	struct s390_load_data data = {0};
	int ret;

	ret = kexec_file_add_image_kernel(image, &data, kernel, kernel_len);
	if (ret)
		return ERR_PTR(ret);

	if (initrd) {
		ret = kexec_file_add_initrd(image, &data, initrd, initrd_len);
		if (ret)
			return ERR_PTR(ret);
	}

	ret = kexec_file_add_purgatory(image, &data);
	if (ret)
		return ERR_PTR(ret);

	return kexec_file_update_kernel(image, &data);
}