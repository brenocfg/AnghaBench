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
struct sk_buff {int len; scalar_t__ data; } ;
struct regmap_ibt_context {int /*<<< orphan*/  hdev; int /*<<< orphan*/  op_read; } ;
struct ibt_rp_reg_access {scalar_t__ addr; int /*<<< orphan*/  data; } ;
struct ibt_cp_reg_access {scalar_t__ addr; size_t len; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCI_CMD_TIMEOUT ; 
 int /*<<< orphan*/  IBT_REG_MODE_16BIT ; 
 int /*<<< orphan*/  IBT_REG_MODE_32BIT ; 
 int /*<<< orphan*/  IBT_REG_MODE_8BIT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct sk_buff* hci_cmd_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ibt_cp_reg_access*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int regmap_ibt_read(void *context, const void *addr, size_t reg_size,
			   void *val, size_t val_size)
{
	struct regmap_ibt_context *ctx = context;
	struct ibt_cp_reg_access cp;
	struct ibt_rp_reg_access *rp;
	struct sk_buff *skb;
	int err = 0;

	if (reg_size != sizeof(__le32))
		return -EINVAL;

	switch (val_size) {
	case 1:
		cp.mode = IBT_REG_MODE_8BIT;
		break;
	case 2:
		cp.mode = IBT_REG_MODE_16BIT;
		break;
	case 4:
		cp.mode = IBT_REG_MODE_32BIT;
		break;
	default:
		return -EINVAL;
	}

	/* regmap provides a little-endian formatted addr */
	cp.addr = *(__le32 *)addr;
	cp.len = val_size;

	bt_dev_dbg(ctx->hdev, "Register (0x%x) read", le32_to_cpu(cp.addr));

	skb = hci_cmd_sync(ctx->hdev, ctx->op_read, sizeof(cp), &cp,
			   HCI_CMD_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error (%d)",
			   le32_to_cpu(cp.addr), err);
		return err;
	}

	if (skb->len != sizeof(*rp) + val_size) {
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error, bad len",
			   le32_to_cpu(cp.addr));
		err = -EINVAL;
		goto done;
	}

	rp = (struct ibt_rp_reg_access *)skb->data;

	if (rp->addr != cp.addr) {
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error, bad addr",
			   le32_to_cpu(rp->addr));
		err = -EINVAL;
		goto done;
	}

	memcpy(val, rp->data, val_size);

done:
	kfree_skb(skb);
	return err;
}