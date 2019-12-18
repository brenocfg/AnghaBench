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
typedef  int u8 ;
typedef  int u16 ;
struct anybus_mbox_hdr {int /*<<< orphan*/  info; } ;
struct mbox_priv {int* msg; int msg_in_sz; struct anybus_mbox_hdr hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EIO ; 
 int /*<<< orphan*/ * EMSGS ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  log_invalid_other (struct device*,struct anybus_mbox_hdr*) ; 

__attribute__((used)) static int mbox_cmd_err(struct device *dev, struct mbox_priv *mpriv)
{
	int i;
	u8 ecode;
	struct anybus_mbox_hdr *hdr = &mpriv->hdr;
	u16 info = be16_to_cpu(hdr->info);
	u8 *phdr = (u8 *)hdr;
	u8 *pmsg = mpriv->msg;

	if (!(info & 0x8000))
		return 0;
	ecode = (info >> 8) & 0x0F;
	dev_err(dev, "mailbox command failed:");
	if (ecode == 0x0F)
		log_invalid_other(dev, hdr);
	else if (ecode < ARRAY_SIZE(EMSGS))
		dev_err(dev, "   Error code: %s (0x%02X)",
			EMSGS[ecode], ecode);
	else
		dev_err(dev, "   Error code: 0x%02X\n", ecode);
	dev_err(dev, "Failed command:");
	dev_err(dev, "Message Header:");
	for (i = 0; i < sizeof(mpriv->hdr); i += 2)
		dev_err(dev, "%02X%02X", phdr[i], phdr[i + 1]);
	dev_err(dev, "Message Data:");
	for (i = 0; i < mpriv->msg_in_sz; i += 2)
		dev_err(dev, "%02X%02X", pmsg[i], pmsg[i + 1]);
	dev_err(dev, "Stack dump:");
	dump_stack();
	return -EIO;
}