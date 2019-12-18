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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {void* length; void* type; } ;
struct TYPE_3__ {void* version; void* length; void* type; } ;
struct i2400m_cmd_enter_power_save {int /*<<< orphan*/  val; TYPE_2__ tlv; TYPE_1__ hdr; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  strerr ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2400M_L3L4_VERSION ; 
 int I2400M_MT_CMD_ENTER_POWERSAVE ; 
 int I2400M_TLV_TYPE_WAKEUP_MODE ; 
 int /*<<< orphan*/  I2400M_WAKEUP_ENABLED ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_check_status (int /*<<< orphan*/ ,char*,int) ; 
 struct sk_buff* i2400m_msg_to_dev (struct i2400m*,struct i2400m_cmd_enter_power_save*,int) ; 
 int /*<<< orphan*/  kfree (struct i2400m_cmd_enter_power_save*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct i2400m_cmd_enter_power_save* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wimax_msg_data (struct sk_buff*) ; 

int i2400m_cmd_enter_powersave(struct i2400m *i2400m)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *ack_skb;
	struct i2400m_cmd_enter_power_save *cmd;
	char strerr[32];

	result = -ENOMEM;
	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		goto error_alloc;
	cmd->hdr.type = cpu_to_le16(I2400M_MT_CMD_ENTER_POWERSAVE);
	cmd->hdr.length = cpu_to_le16(sizeof(*cmd) - sizeof(cmd->hdr));
	cmd->hdr.version = cpu_to_le16(I2400M_L3L4_VERSION);
	cmd->tlv.type = cpu_to_le16(I2400M_TLV_TYPE_WAKEUP_MODE);
	cmd->tlv.length = cpu_to_le16(sizeof(cmd->val));
	cmd->val = cpu_to_le32(I2400M_WAKEUP_ENABLED);

	ack_skb = i2400m_msg_to_dev(i2400m, cmd, sizeof(*cmd));
	result = PTR_ERR(ack_skb);
	if (IS_ERR(ack_skb)) {
		dev_err(dev, "Failed to issue 'Enter power save' command: %d\n",
			result);
		goto error_msg_to_dev;
	}
	result = i2400m_msg_check_status(wimax_msg_data(ack_skb),
					 strerr, sizeof(strerr));
	if (result == -EACCES)
		d_printf(1, dev, "Cannot enter power save mode\n");
	else if (result < 0)
		dev_err(dev, "'Enter power save' (0x%04x) command failed: "
			"%d - %s\n", I2400M_MT_CMD_ENTER_POWERSAVE,
			result, strerr);
	else
		d_printf(1, dev, "device ready to power save\n");
	kfree_skb(ack_skb);
error_msg_to_dev:
	kfree(cmd);
error_alloc:
	return result;
}