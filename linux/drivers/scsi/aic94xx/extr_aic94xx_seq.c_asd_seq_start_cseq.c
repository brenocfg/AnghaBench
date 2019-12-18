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
 int /*<<< orphan*/  CPRGMCNT ; 
 int asd_unpause_cseq (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cseq_idle_loop ; 

__attribute__((used)) static int asd_seq_start_cseq(struct asd_ha_struct *asd_ha)
{
	/* Reset the ARP2 instruction to location zero. */
	asd_write_reg_word(asd_ha, CPRGMCNT, cseq_idle_loop);

	/* Unpause the CSEQ  */
	return asd_unpause_cseq(asd_ha);
}