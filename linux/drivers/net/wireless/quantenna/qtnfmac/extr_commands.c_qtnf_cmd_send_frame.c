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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd_frame_tx {void* flags; void* freq; int /*<<< orphan*/  cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_SEND_FRAME ; 
 int QTNF_MAX_CMD_BUF_SIZE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_buffer (struct sk_buff*,int /*<<< orphan*/  const*,size_t) ; 

int qtnf_cmd_send_frame(struct qtnf_vif *vif, u32 cookie, u16 flags,
			u16 freq, const u8 *buf, size_t len)
{
	struct sk_buff *cmd_skb;
	struct qlink_cmd_frame_tx *cmd;
	int ret;

	if (sizeof(*cmd) + len > QTNF_MAX_CMD_BUF_SIZE) {
		pr_warn("VIF%u.%u: frame is too big: %zu\n", vif->mac->macid,
			vif->vifid, len);
		return -E2BIG;
	}

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_SEND_FRAME,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	cmd = (struct qlink_cmd_frame_tx *)cmd_skb->data;
	cmd->cookie = cpu_to_le32(cookie);
	cmd->freq = cpu_to_le16(freq);
	cmd->flags = cpu_to_le16(flags);

	if (len && buf)
		qtnf_cmd_skb_put_buffer(cmd_skb, buf, len);

	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(vif->mac->bus);

	return ret;
}