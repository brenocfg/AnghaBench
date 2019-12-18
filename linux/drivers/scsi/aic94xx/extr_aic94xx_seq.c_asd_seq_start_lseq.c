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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LmPRGMCNT (int) ; 
 int asd_seq_unpause_lseq (struct asd_ha_struct*,int) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseq_idle_loop ; 

__attribute__((used)) static int asd_seq_start_lseq(struct asd_ha_struct *asd_ha, int lseq)
{
	/* Reset the ARP2 instruction to location zero. */
	asd_write_reg_word(asd_ha, LmPRGMCNT(lseq), lseq_idle_loop);

	/* Unpause the LmSEQ  */
	return asd_seq_unpause_lseq(asd_ha, lseq);
}