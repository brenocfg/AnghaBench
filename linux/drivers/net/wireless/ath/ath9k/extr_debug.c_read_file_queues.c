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
struct seq_file {int /*<<< orphan*/  private; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_txq {int dummy; } ;
struct TYPE_4__ {struct ath_txq* cabq; } ;
struct TYPE_3__ {struct ath_txq** txq_map; } ;
struct ath_softc {TYPE_2__ beacon; TYPE_1__ tx; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 struct ieee80211_hw* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_queue (struct ath_softc*,struct ath_txq*,struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int read_file_queues(struct seq_file *file, void *data)
{
	struct ieee80211_hw *hw = dev_get_drvdata(file->private);
	struct ath_softc *sc = hw->priv;
	struct ath_txq *txq;
	int i;
	static const char *qname[4] = {
		"VO", "VI", "BE", "BK"
	};

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = sc->tx.txq_map[i];
		seq_printf(file, "(%s):  ", qname[i]);
		print_queue(sc, txq, file);
	}

	seq_puts(file, "(CAB): ");
	print_queue(sc, sc->beacon.cabq, file);

	return 0;
}