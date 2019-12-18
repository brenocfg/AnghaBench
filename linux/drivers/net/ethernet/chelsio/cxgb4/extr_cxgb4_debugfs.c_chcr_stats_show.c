#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct adapter* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipsec_cnt; int /*<<< orphan*/  fallback; int /*<<< orphan*/  error; int /*<<< orphan*/  complete; int /*<<< orphan*/  aead_rqst; int /*<<< orphan*/  digest_rqst; int /*<<< orphan*/  cipher_rqst; } ;
struct adapter {TYPE_1__ chcr_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int chcr_stats_show(struct seq_file *seq, void *v)
{
	struct adapter *adap = seq->private;

	seq_puts(seq, "Chelsio Crypto Accelerator Stats \n");
	seq_printf(seq, "Cipher Ops: %10u \n",
		   atomic_read(&adap->chcr_stats.cipher_rqst));
	seq_printf(seq, "Digest Ops: %10u \n",
		   atomic_read(&adap->chcr_stats.digest_rqst));
	seq_printf(seq, "Aead Ops: %10u \n",
		   atomic_read(&adap->chcr_stats.aead_rqst));
	seq_printf(seq, "Completion: %10u \n",
		   atomic_read(&adap->chcr_stats.complete));
	seq_printf(seq, "Error: %10u \n",
		   atomic_read(&adap->chcr_stats.error));
	seq_printf(seq, "Fallback: %10u \n",
		   atomic_read(&adap->chcr_stats.fallback));
	seq_printf(seq, "IPSec PDU: %10u\n",
		   atomic_read(&adap->chcr_stats.ipsec_cnt));
	return 0;
}