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
 int pblk_calc_secs (struct pblk*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int pblk_calc_secs_to_sync(struct pblk *pblk, unsigned int secs_avail,
				  unsigned int secs_to_flush)
{
	int secs_to_sync;

	secs_to_sync = pblk_calc_secs(pblk, secs_avail, secs_to_flush, true);

#ifdef CONFIG_NVM_PBLK_DEBUG
	if ((!secs_to_sync && secs_to_flush)
			|| (secs_to_sync < 0)
			|| (secs_to_sync > secs_avail && !secs_to_flush)) {
		pblk_err(pblk, "bad sector calculation (a:%d,s:%d,f:%d)\n",
				secs_avail, secs_to_sync, secs_to_flush);
	}
#endif

	return secs_to_sync;
}