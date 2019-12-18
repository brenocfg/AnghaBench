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
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_free (struct pblk*) ; 
 int /*<<< orphan*/  pblk_gc_exit (struct pblk*,int) ; 
 int /*<<< orphan*/  pblk_info (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_l2p_crc (struct pblk*) ; 
 int /*<<< orphan*/  pblk_tear_down (struct pblk*,int) ; 

__attribute__((used)) static void pblk_exit(void *private, bool graceful)
{
	struct pblk *pblk = private;

	pblk_gc_exit(pblk, graceful);
	pblk_tear_down(pblk, graceful);

#ifdef CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "exit: L2P CRC: %x\n", pblk_l2p_crc(pblk));
#endif

	pblk_free(pblk);
}