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
typedef  int /*<<< orphan*/  u32 ;
struct cw1200_common {int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ST90TDS_SRAM_BASE_ADDR_REG_ID ; 
 int /*<<< orphan*/  ST90TDS_SRAM_DPORT_REG_ID ; 
 int __cw1200_reg_write (struct cw1200_common*,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int __cw1200_reg_write_32 (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int cw1200_apb_write(struct cw1200_common *priv, u32 addr, const void *buf,
			size_t buf_len)
{
	int ret;

	if ((buf_len / 2) >= 0x1000) {
		pr_err("Can't write more than 0xfff words.\n");
		return -EINVAL;
	}

	priv->hwbus_ops->lock(priv->hwbus_priv);

	/* Write address */
	ret = __cw1200_reg_write_32(priv, ST90TDS_SRAM_BASE_ADDR_REG_ID, addr);
	if (ret < 0) {
		pr_err("Can't write address register.\n");
		goto out;
	}

	/* Write data port */
	ret = __cw1200_reg_write(priv, ST90TDS_SRAM_DPORT_REG_ID,
					buf, buf_len, 0);
	if (ret < 0) {
		pr_err("Can't write data port.\n");
		goto out;
	}

out:
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	return ret;
}