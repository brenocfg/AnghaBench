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
struct cw1200_common {int buf_id_rx; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_RETRY ; 
 int /*<<< orphan*/  ST90TDS_IN_OUT_QUEUE_REG_ID ; 
 int __cw1200_reg_read (struct cw1200_common*,int /*<<< orphan*/ ,void*,size_t,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int cw1200_data_read(struct cw1200_common *priv, void *buf, size_t buf_len)
{
	int ret, retry = 1;
	int buf_id_rx = priv->buf_id_rx;

	priv->hwbus_ops->lock(priv->hwbus_priv);

	while (retry <= MAX_RETRY) {
		ret = __cw1200_reg_read(priv,
					ST90TDS_IN_OUT_QUEUE_REG_ID, buf,
					buf_len, buf_id_rx + 1);
		if (!ret) {
			buf_id_rx = (buf_id_rx + 1) & 3;
			priv->buf_id_rx = buf_id_rx;
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