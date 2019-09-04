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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int vpe_release(struct inode *inode, struct file *filp)
{
#if defined(CONFIG_MIPS_VPE_LOADER_MT) || defined(CONFIG_MIPS_VPE_LOADER_CMP)
	struct vpe *v;
	Elf_Ehdr *hdr;
	int ret = 0;

	v = get_vpe(aprp_cpu_index());
	if (v == NULL)
		return -ENODEV;

	hdr = (Elf_Ehdr *) v->pbuffer;
	if (memcmp(hdr->e_ident, ELFMAG, SELFMAG) == 0) {
		if (vpe_elfload(v) >= 0) {
			vpe_run(v);
		} else {
			pr_warn("VPE loader: ELF load failed.\n");
			ret = -ENOEXEC;
		}
	} else {
		pr_warn("VPE loader: only elf files are supported\n");
		ret = -ENOEXEC;
	}

	/* It's good to be able to run the SP and if it chokes have a look at
	   the /dev/rt?. But if we reset the pointer to the shared struct we
	   lose what has happened. So perhaps if garbage is sent to the vpe
	   device, use it as a trigger for the reset. Hopefully a nice
	   executable will be along shortly. */
	if (ret < 0)
		v->shared_ptr = NULL;

	vfree(v->pbuffer);
	v->plen = 0;

	return ret;
#else
	pr_warn("VPE loader: ELF load failed.\n");
	return -ENOEXEC;
#endif
}