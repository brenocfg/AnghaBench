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
struct ppa_addr {int dummy; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int nr_ppas; int is_seq; int /*<<< orphan*/ * bio; struct ppa_addr ppa_addr; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVM_OP_ERASE ; 

__attribute__((used)) static void pblk_setup_e_rq(struct pblk *pblk, struct nvm_rq *rqd,
			    struct ppa_addr ppa)
{
	rqd->opcode = NVM_OP_ERASE;
	rqd->ppa_addr = ppa;
	rqd->nr_ppas = 1;
	rqd->is_seq = 1;
	rqd->bio = NULL;
}