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
struct kimage {int dummy; } ;
typedef  int /*<<< orphan*/  kernel_load_addr ;
typedef  int /*<<< orphan*/  fdt_load_addr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLAVE_CODE_SIZE ; 
 int kexec_purgatory_get_set_symbol (struct kimage*,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,void const*,int) ; 

int setup_purgatory(struct kimage *image, const void *slave_code,
		    const void *fdt, unsigned long kernel_load_addr,
		    unsigned long fdt_load_addr)
{
	unsigned int *slave_code_buf, master_entry;
	int ret;

	slave_code_buf = kmalloc(SLAVE_CODE_SIZE, GFP_KERNEL);
	if (!slave_code_buf)
		return -ENOMEM;

	/* Get the slave code from the new kernel and put it in purgatory. */
	ret = kexec_purgatory_get_set_symbol(image, "purgatory_start",
					     slave_code_buf, SLAVE_CODE_SIZE,
					     true);
	if (ret) {
		kfree(slave_code_buf);
		return ret;
	}

	master_entry = slave_code_buf[0];
	memcpy(slave_code_buf, slave_code, SLAVE_CODE_SIZE);
	slave_code_buf[0] = master_entry;
	ret = kexec_purgatory_get_set_symbol(image, "purgatory_start",
					     slave_code_buf, SLAVE_CODE_SIZE,
					     false);
	kfree(slave_code_buf);

	ret = kexec_purgatory_get_set_symbol(image, "kernel", &kernel_load_addr,
					     sizeof(kernel_load_addr), false);
	if (ret)
		return ret;
	ret = kexec_purgatory_get_set_symbol(image, "dt_offset", &fdt_load_addr,
					     sizeof(fdt_load_addr), false);
	if (ret)
		return ret;

	return 0;
}