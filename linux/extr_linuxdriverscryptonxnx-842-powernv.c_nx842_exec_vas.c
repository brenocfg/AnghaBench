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
typedef  scalar_t__ u32 ;
struct vas_window {int dummy; } ;
struct coprocessor_status_block {int /*<<< orphan*/  count; } ;
struct coprocessor_request_block {int /*<<< orphan*/  ccw; struct coprocessor_status_block csb; } ;
struct nx842_workmem {int /*<<< orphan*/  start; struct coprocessor_request_block crb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FC_842 ; 
 struct nx842_workmem* PTR_ALIGN (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ SET_FIELD (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  VAS_RETRIES ; 
 int /*<<< orphan*/  WORKMEM_ALIGN ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_txwin ; 
 int /*<<< orphan*/  ktime_get () ; 
 int nx842_config_crb (unsigned char const*,unsigned int,unsigned char*,unsigned int,struct nx842_workmem*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct vas_window* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vas_copy_crb (struct coprocessor_request_block*,int /*<<< orphan*/ ) ; 
 int vas_paste_crb (struct vas_window*,int /*<<< orphan*/ ,int) ; 
 int wait_for_csb (struct nx842_workmem*,struct coprocessor_status_block*) ; 

__attribute__((used)) static int nx842_exec_vas(const unsigned char *in, unsigned int inlen,
				  unsigned char *out, unsigned int *outlenp,
				  void *workmem, int fc)
{
	struct coprocessor_request_block *crb;
	struct coprocessor_status_block *csb;
	struct nx842_workmem *wmem;
	struct vas_window *txwin;
	int ret, i = 0;
	u32 ccw;
	unsigned int outlen = *outlenp;

	wmem = PTR_ALIGN(workmem, WORKMEM_ALIGN);

	*outlenp = 0;

	crb = &wmem->crb;
	csb = &crb->csb;

	ret = nx842_config_crb(in, inlen, out, outlen, wmem);
	if (ret)
		return ret;

	ccw = 0;
	ccw = SET_FIELD(CCW_FC_842, ccw, fc);
	crb->ccw = cpu_to_be32(ccw);

	do {
		wmem->start = ktime_get();
		preempt_disable();
		txwin = this_cpu_read(cpu_txwin);

		/*
		 * VAS copy CRB into L2 cache. Refer <asm/vas.h>.
		 * @crb and @offset.
		 */
		vas_copy_crb(crb, 0);

		/*
		 * VAS paste previously copied CRB to NX.
		 * @txwin, @offset and @last (must be true).
		 */
		ret = vas_paste_crb(txwin, 0, 1);
		preempt_enable();
		/*
		 * Retry copy/paste function for VAS failures.
		 */
	} while (ret && (i++ < VAS_RETRIES));

	if (ret) {
		pr_err_ratelimited("VAS copy/paste failed\n");
		return ret;
	}

	ret = wait_for_csb(wmem, csb);
	if (!ret)
		*outlenp = be32_to_cpu(csb->count);

	return ret;
}