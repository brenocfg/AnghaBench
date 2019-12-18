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
typedef  int u32 ;
struct ocotp_priv {int /*<<< orphan*/  nvmem_ipc; TYPE_1__* data; } ;
struct TYPE_2__ {int nregs; scalar_t__ devtype; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMX8QXP ; 
 int imx_sc_misc_otp_fuse_read (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int round_up (unsigned int,int) ; 

__attribute__((used)) static int imx_scu_ocotp_read(void *context, unsigned int offset,
			      void *val, size_t bytes)
{
	struct ocotp_priv *priv = context;
	u32 count, index, num_bytes;
	u32 *buf;
	void *p;
	int i, ret;

	index = offset >> 2;
	num_bytes = round_up((offset % 4) + bytes, 4);
	count = num_bytes >> 2;

	if (count > (priv->data->nregs - index))
		count = priv->data->nregs - index;

	p = kzalloc(num_bytes, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	buf = p;

	for (i = index; i < (index + count); i++) {
		if (priv->data->devtype == IMX8QXP) {
			if ((i > 271) && (i < 544)) {
				*buf++ = 0;
				continue;
			}
		}

		ret = imx_sc_misc_otp_fuse_read(priv->nvmem_ipc, i, buf);
		if (ret) {
			kfree(p);
			return ret;
		}
		buf++;
	}

	memcpy(val, (u8 *)p + offset % 4, bytes);

	kfree(p);

	return 0;
}