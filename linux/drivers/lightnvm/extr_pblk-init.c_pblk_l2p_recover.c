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
struct pblk_line {int dummy; } ;
struct pblk {int /*<<< orphan*/  instance_uuid; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IS_ERR (struct pblk_line*) ; 
 int /*<<< orphan*/  guid_gen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  pblk_gc_free_full_lines (struct pblk*) ; 
 int /*<<< orphan*/  pblk_info (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_l2p_crc (struct pblk*) ; 
 struct pblk_line* pblk_line_get_first_data (struct pblk*) ; 
 struct pblk_line* pblk_recov_l2p (struct pblk*) ; 

__attribute__((used)) static int pblk_l2p_recover(struct pblk *pblk, bool factory_init)
{
	struct pblk_line *line = NULL;

	if (factory_init) {
		guid_gen(&pblk->instance_uuid);
	} else {
		line = pblk_recov_l2p(pblk);
		if (IS_ERR(line)) {
			pblk_err(pblk, "could not recover l2p table\n");
			return -EFAULT;
		}
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "init: L2P CRC: %x\n", pblk_l2p_crc(pblk));
#endif

	/* Free full lines directly as GC has not been started yet */
	pblk_gc_free_full_lines(pblk);

	if (!line) {
		/* Configure next line for user data */
		line = pblk_line_get_first_data(pblk);
		if (!line)
			return -EFAULT;
	}

	return 0;
}