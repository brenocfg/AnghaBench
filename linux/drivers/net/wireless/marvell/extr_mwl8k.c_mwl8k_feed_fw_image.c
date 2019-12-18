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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mwl8k_priv {scalar_t__ regs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MWL8K_HIU_SCRATCH ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 
 int mwl8k_send_fw_load_cmd (struct mwl8k_priv*,unsigned char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mwl8k_feed_fw_image(struct mwl8k_priv *priv,
				const u8 *data, size_t length)
{
	unsigned char *buffer;
	int may_continue, rc = 0;
	u32 done, prev_block_size;

	buffer = kmalloc(1024, GFP_KERNEL);
	if (buffer == NULL)
		return -ENOMEM;

	done = 0;
	prev_block_size = 0;
	may_continue = 1000;
	while (may_continue > 0) {
		u32 block_size;

		block_size = ioread32(priv->regs + MWL8K_HIU_SCRATCH);
		if (block_size & 1) {
			block_size &= ~1;
			may_continue--;
		} else {
			done += prev_block_size;
			length -= prev_block_size;
		}

		if (block_size > 1024 || block_size > length) {
			rc = -EOVERFLOW;
			break;
		}

		if (length == 0) {
			rc = 0;
			break;
		}

		if (block_size == 0) {
			rc = -EPROTO;
			may_continue--;
			udelay(1);
			continue;
		}

		prev_block_size = block_size;
		memcpy(buffer, data + done, block_size);

		rc = mwl8k_send_fw_load_cmd(priv, buffer, block_size);
		if (rc)
			break;
	}

	if (!rc && length != 0)
		rc = -EREMOTEIO;

	kfree(buffer);

	return rc;
}