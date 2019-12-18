#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct st21nfca_pipe_info {scalar_t__ dst_gate_id; scalar_t__ src_host_id; int /*<<< orphan*/  pipe_state; } ;
struct sk_buff {int len; size_t* data; } ;
struct TYPE_7__ {TYPE_1__* gates; } ;
struct nfc_hci_dev {size_t* gate2pipe; TYPE_3__* pipes; TYPE_2__ init_data; } ;
typedef  int /*<<< orphan*/  pipe_list ;
typedef  int /*<<< orphan*/  pipe_info ;
struct TYPE_9__ {size_t gate; } ;
struct TYPE_8__ {size_t gate; scalar_t__ dest_host; } ;
struct TYPE_6__ {size_t pipe; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  NFC_HCI_HOST_CONTROLLER_ID ; 
 int /*<<< orphan*/  NFC_HCI_LINK_MGMT_GATE ; 
 int /*<<< orphan*/  NFC_HCI_LINK_MGMT_PIPE ; 
 size_t NFC_HCI_TERMINAL_HOST_ID ; 
 scalar_t__ NFC_HCI_UICC_HOST_ID ; 
 scalar_t__ ST21NFCA_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST21NFCA_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST21NFCA_DEVICE_MGNT_PIPE ; 
 int /*<<< orphan*/  ST21NFCA_DM_GETINFO ; 
 size_t ST21NFCA_DM_GETINFO_PIPE_INFO ; 
 size_t ST21NFCA_DM_GETINFO_PIPE_LIST ; 
 scalar_t__ ST21NFCA_DM_IS_PIPE_OPEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_connect_gate (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_hci_send_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 TYPE_4__* st21nfca_gates ; 

__attribute__((used)) static int st21nfca_hci_load_session(struct nfc_hci_dev *hdev)
{
	int i, j, r;
	struct sk_buff *skb_pipe_list, *skb_pipe_info;
	struct st21nfca_pipe_info *info;

	u8 pipe_list[] = { ST21NFCA_DM_GETINFO_PIPE_LIST,
		NFC_HCI_TERMINAL_HOST_ID
	};
	u8 pipe_info[] = { ST21NFCA_DM_GETINFO_PIPE_INFO,
		NFC_HCI_TERMINAL_HOST_ID, 0
	};

	/* On ST21NFCA device pipes number are dynamics
	 * A maximum of 16 pipes can be created at the same time
	 * If pipes are already created, hci_dev_up will fail.
	 * Doing a clear all pipe is a bad idea because:
	 * - It does useless EEPROM cycling
	 * - It might cause issue for secure elements support
	 * (such as removing connectivity or APDU reader pipe)
	 * A better approach on ST21NFCA is to:
	 * - get a pipe list for each host.
	 * (eg: NFC_HCI_HOST_CONTROLLER_ID for now).
	 * (TODO Later on UICC HOST and eSE HOST)
	 * - get pipe information
	 * - match retrieved pipe list in st21nfca_gates
	 * ST21NFCA_DEVICE_MGNT_GATE is a proprietary gate
	 * with ST21NFCA_DEVICE_MGNT_PIPE.
	 * Pipe can be closed and need to be open.
	 */
	r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
				ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_DEVICE_MGNT_PIPE);
	if (r < 0)
		return r;

	/* Get pipe list */
	r = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_DM_GETINFO, pipe_list, sizeof(pipe_list),
			&skb_pipe_list);
	if (r < 0)
		return r;

	/* Complete the existing gate_pipe table */
	for (i = 0; i < skb_pipe_list->len; i++) {
		pipe_info[2] = skb_pipe_list->data[i];
		r = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
					ST21NFCA_DM_GETINFO, pipe_info,
					sizeof(pipe_info), &skb_pipe_info);
		if (r)
			continue;

		/*
		 * Match pipe ID and gate ID
		 * Output format from ST21NFC_DM_GETINFO is:
		 * - pipe state (1byte)
		 * - source hid (1byte)
		 * - source gid (1byte)
		 * - destination hid (1byte)
		 * - destination gid (1byte)
		 */
		info = (struct st21nfca_pipe_info *) skb_pipe_info->data;
		if (info->dst_gate_id == ST21NFCA_APDU_READER_GATE &&
			info->src_host_id == NFC_HCI_UICC_HOST_ID) {
			pr_err("Unexpected apdu_reader pipe on host %x\n",
				info->src_host_id);
			kfree_skb(skb_pipe_info);
			continue;
		}

		for (j = 3; (j < ARRAY_SIZE(st21nfca_gates)) &&
			(st21nfca_gates[j].gate != info->dst_gate_id) ; j++)
			;

		if (j < ARRAY_SIZE(st21nfca_gates) &&
			st21nfca_gates[j].gate == info->dst_gate_id &&
			ST21NFCA_DM_IS_PIPE_OPEN(info->pipe_state)) {
			hdev->init_data.gates[j].pipe = pipe_info[2];

			hdev->gate2pipe[st21nfca_gates[j].gate] =
						pipe_info[2];
			hdev->pipes[pipe_info[2]].gate =
						st21nfca_gates[j].gate;
			hdev->pipes[pipe_info[2]].dest_host =
						info->src_host_id;
		}
		kfree_skb(skb_pipe_info);
	}

	/*
	 * 3 gates have a well known pipe ID. Only NFC_HCI_LINK_MGMT_GATE
	 * is not yet open at this stage.
	 */
	r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
				 NFC_HCI_LINK_MGMT_GATE,
				 NFC_HCI_LINK_MGMT_PIPE);

	kfree_skb(skb_pipe_list);
	return r;
}