#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ar5523_tx_cmd {int olen; int flags; int res; int /*<<< orphan*/ * odata; int /*<<< orphan*/  done; TYPE_1__* urb_tx; scalar_t__ buf_tx; } ;
struct ar5523_cmd_hdr {void* magic; int /*<<< orphan*/  priv; void* code; void* len; } ;
struct ar5523 {int /*<<< orphan*/  dev; struct ar5523_tx_cmd tx_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int AR5523_CMD_FLAG_MAGIC ; 
 int /*<<< orphan*/  AR5523_CMD_ID ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  ar5523_cmd_tx_cb ; 
 int /*<<< orphan*/  ar5523_cmd_tx_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*,int) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int,...) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (struct ar5523_cmd_hdr*,void const*,int) ; 
 int /*<<< orphan*/  memset (struct ar5523_cmd_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct ar5523_tx_cmd*) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ar5523_cmd(struct ar5523 *ar, u32 code, const void *idata,
		      int ilen, void *odata, int olen, int flags)
{
	struct ar5523_cmd_hdr *hdr;
	struct ar5523_tx_cmd *cmd = &ar->tx_cmd;
	int xferlen, error;

	/* always bulk-out a multiple of 4 bytes */
	xferlen = (sizeof(struct ar5523_cmd_hdr) + ilen + 3) & ~3;

	hdr = (struct ar5523_cmd_hdr *)cmd->buf_tx;
	memset(hdr, 0, sizeof(struct ar5523_cmd_hdr));
	hdr->len  = cpu_to_be32(xferlen);
	hdr->code = cpu_to_be32(code);
	hdr->priv = AR5523_CMD_ID;

	if (flags & AR5523_CMD_FLAG_MAGIC)
		hdr->magic = cpu_to_be32(1 << 24);
	memcpy(hdr + 1, idata, ilen);

	cmd->odata = odata;
	cmd->olen = olen;
	cmd->flags = flags;

	ar5523_dbg(ar, "do cmd %02x\n", code);

	usb_fill_bulk_urb(cmd->urb_tx, ar->dev, ar5523_cmd_tx_pipe(ar->dev),
			  cmd->buf_tx, xferlen, ar5523_cmd_tx_cb, cmd);
	cmd->urb_tx->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = usb_submit_urb(cmd->urb_tx, GFP_KERNEL);
	if (error) {
		ar5523_err(ar, "could not send command 0x%x, error=%d\n",
			   code, error);
		return error;
	}

	if (!wait_for_completion_timeout(&cmd->done, 2 * HZ)) {
		cmd->odata = NULL;
		ar5523_err(ar, "timeout waiting for command %02x reply\n",
			   code);
		cmd->res = -ETIMEDOUT;
	}
	return cmd->res;
}