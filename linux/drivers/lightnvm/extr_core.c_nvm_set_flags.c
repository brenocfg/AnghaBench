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
struct nvm_rq {scalar_t__ opcode; scalar_t__ is_seq; } ;
struct nvm_geo {scalar_t__ version; int pln_mode; } ;

/* Variables and functions */
 int NVM_IO_SCRAMBLE_ENABLE ; 
 int NVM_IO_SUSPEND ; 
 scalar_t__ NVM_OCSSD_SPEC_20 ; 
 scalar_t__ NVM_OP_PREAD ; 
 scalar_t__ NVM_OP_PWRITE ; 

__attribute__((used)) static int nvm_set_flags(struct nvm_geo *geo, struct nvm_rq *rqd)
{
	int flags = 0;

	if (geo->version == NVM_OCSSD_SPEC_20)
		return 0;

	if (rqd->is_seq)
		flags |= geo->pln_mode >> 1;

	if (rqd->opcode == NVM_OP_PREAD)
		flags |= (NVM_IO_SCRAMBLE_ENABLE | NVM_IO_SUSPEND);
	else if (rqd->opcode == NVM_OP_PWRITE)
		flags |= NVM_IO_SCRAMBLE_ENABLE;

	return flags;
}