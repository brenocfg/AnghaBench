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
typedef  int u64 ;
struct coprocessor_status_block {int dummy; } ;
struct coprocessor_request_block {int /*<<< orphan*/  csb_addr; int /*<<< orphan*/  target; int /*<<< orphan*/  source; struct coprocessor_status_block csb; } ;
struct nx842_workmem {int /*<<< orphan*/  ddl_out; int /*<<< orphan*/  ddl_in; struct coprocessor_request_block crb; } ;

/* Variables and functions */
 int CRB_CSB_ADDRESS ; 
 int CRB_CSB_AT ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (struct coprocessor_request_block*,int /*<<< orphan*/ ,int) ; 
 int nx842_get_pa (struct coprocessor_status_block*) ; 
 int setup_ddl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned int,int) ; 

__attribute__((used)) static int nx842_config_crb(const unsigned char *in, unsigned int inlen,
			unsigned char *out, unsigned int outlen,
			struct nx842_workmem *wmem)
{
	struct coprocessor_request_block *crb;
	struct coprocessor_status_block *csb;
	u64 csb_addr;
	int ret;

	crb = &wmem->crb;
	csb = &crb->csb;

	/* Clear any previous values */
	memset(crb, 0, sizeof(*crb));

	/* set up DDLs */
	ret = setup_ddl(&crb->source, wmem->ddl_in,
			(unsigned char *)in, inlen, true);
	if (ret)
		return ret;

	ret = setup_ddl(&crb->target, wmem->ddl_out,
			out, outlen, false);
	if (ret)
		return ret;

	/* set up CRB's CSB addr */
	csb_addr = nx842_get_pa(csb) & CRB_CSB_ADDRESS;
	csb_addr |= CRB_CSB_AT; /* Addrs are phys */
	crb->csb_addr = cpu_to_be64(csb_addr);

	return 0;
}