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
typedef  int umode_t ;
struct qca_data {int /*<<< orphan*/  tx_idle_delay; int /*<<< orphan*/  wake_retrans; int /*<<< orphan*/  vote_off_ms; int /*<<< orphan*/  vote_on_ms; int /*<<< orphan*/  votes_off; int /*<<< orphan*/  votes_on; int /*<<< orphan*/  rx_votes_off; int /*<<< orphan*/  rx_votes_on; int /*<<< orphan*/  rx_vote; int /*<<< orphan*/  tx_votes_off; int /*<<< orphan*/  tx_votes_on; int /*<<< orphan*/  tx_vote; int /*<<< orphan*/  ibs_recv_wacks; int /*<<< orphan*/  ibs_recv_wakes; int /*<<< orphan*/  ibs_recv_slps; int /*<<< orphan*/  ibs_sent_wacks; int /*<<< orphan*/  ibs_sent_wakes; int /*<<< orphan*/  ibs_sent_slps; int /*<<< orphan*/  rx_ibs_state; int /*<<< orphan*/  tx_ibs_state; } ;
struct hci_uart {struct qca_data* priv; } ;
struct hci_dev {int /*<<< orphan*/  debugfs; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u64 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 

__attribute__((used)) static void qca_debugfs_init(struct hci_dev *hdev)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct qca_data *qca = hu->priv;
	struct dentry *ibs_dir;
	umode_t mode;

	if (!hdev->debugfs)
		return;

	ibs_dir = debugfs_create_dir("ibs", hdev->debugfs);

	/* read only */
	mode = S_IRUGO;
	debugfs_create_u8("tx_ibs_state", mode, ibs_dir, &qca->tx_ibs_state);
	debugfs_create_u8("rx_ibs_state", mode, ibs_dir, &qca->rx_ibs_state);
	debugfs_create_u64("ibs_sent_sleeps", mode, ibs_dir,
			   &qca->ibs_sent_slps);
	debugfs_create_u64("ibs_sent_wakes", mode, ibs_dir,
			   &qca->ibs_sent_wakes);
	debugfs_create_u64("ibs_sent_wake_acks", mode, ibs_dir,
			   &qca->ibs_sent_wacks);
	debugfs_create_u64("ibs_recv_sleeps", mode, ibs_dir,
			   &qca->ibs_recv_slps);
	debugfs_create_u64("ibs_recv_wakes", mode, ibs_dir,
			   &qca->ibs_recv_wakes);
	debugfs_create_u64("ibs_recv_wake_acks", mode, ibs_dir,
			   &qca->ibs_recv_wacks);
	debugfs_create_bool("tx_vote", mode, ibs_dir, &qca->tx_vote);
	debugfs_create_u64("tx_votes_on", mode, ibs_dir, &qca->tx_votes_on);
	debugfs_create_u64("tx_votes_off", mode, ibs_dir, &qca->tx_votes_off);
	debugfs_create_bool("rx_vote", mode, ibs_dir, &qca->rx_vote);
	debugfs_create_u64("rx_votes_on", mode, ibs_dir, &qca->rx_votes_on);
	debugfs_create_u64("rx_votes_off", mode, ibs_dir, &qca->rx_votes_off);
	debugfs_create_u64("votes_on", mode, ibs_dir, &qca->votes_on);
	debugfs_create_u64("votes_off", mode, ibs_dir, &qca->votes_off);
	debugfs_create_u32("vote_on_ms", mode, ibs_dir, &qca->vote_on_ms);
	debugfs_create_u32("vote_off_ms", mode, ibs_dir, &qca->vote_off_ms);

	/* read/write */
	mode = S_IRUGO | S_IWUSR;
	debugfs_create_u32("wake_retrans", mode, ibs_dir, &qca->wake_retrans);
	debugfs_create_u32("tx_idle_delay", mode, ibs_dir,
			   &qca->tx_idle_delay);
}