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
struct cw1200_common {int buf_id_tx; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_RETRY ; 
 int /*<<< orphan*/  ST90TDS_IN_OUT_QUEUE_REG_ID ; 
 int __cw1200_reg_write (struct cw1200_common*,int /*<<< orphan*/ ,void const*,size_t,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int cw1200_data_write(struct cw1200_common *priv, const void *buf,
			size_t buf_len)
{
	int ret, retry = 1;
	int buf_id_tx = priv->buf_id_tx;

	priv->hwbus_ops->lock(priv->hwbus_priv);

	while (retry <= MAX_RETRY) {
		ret = __cw1200_reg_write(priv,
					 ST90TDS_IN_OUT_QUEUE_REG_ID, buf,
					 buf_len, buf_id_tx);
		if (!ret) {
			buf_id_tx = (buf_id_tx + 1) & 31;
			priv->buf_id_tx = buf_id_tx;
			break;
		} else {
			retry++;
			mdelay(1);
			pr_err("error :[%d]\n", ret);
		}
	}

	priv->hwbus_ops->unlock(priv->hwbus_priv);
	return ret;
}