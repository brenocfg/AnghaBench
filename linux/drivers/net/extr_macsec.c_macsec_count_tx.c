#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  OutPktsProtected; int /*<<< orphan*/  OutOctetsProtected; int /*<<< orphan*/  OutPktsEncrypted; int /*<<< orphan*/  OutOctetsEncrypted; } ;
struct pcpu_tx_sc_stats {int /*<<< orphan*/  syncp; TYPE_1__ stats; } ;
struct macsec_tx_sc {scalar_t__ encrypt; int /*<<< orphan*/  stats; } ;
struct macsec_tx_sa {TYPE_2__* stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  OutPktsProtected; int /*<<< orphan*/  OutPktsEncrypted; } ;

/* Variables and functions */
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct pcpu_tx_sc_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void macsec_count_tx(struct sk_buff *skb, struct macsec_tx_sc *tx_sc,
			    struct macsec_tx_sa *tx_sa)
{
	struct pcpu_tx_sc_stats *txsc_stats = this_cpu_ptr(tx_sc->stats);

	u64_stats_update_begin(&txsc_stats->syncp);
	if (tx_sc->encrypt) {
		txsc_stats->stats.OutOctetsEncrypted += skb->len;
		txsc_stats->stats.OutPktsEncrypted++;
		this_cpu_inc(tx_sa->stats->OutPktsEncrypted);
	} else {
		txsc_stats->stats.OutOctetsProtected += skb->len;
		txsc_stats->stats.OutPktsProtected++;
		this_cpu_inc(tx_sa->stats->OutPktsProtected);
	}
	u64_stats_update_end(&txsc_stats->syncp);
}