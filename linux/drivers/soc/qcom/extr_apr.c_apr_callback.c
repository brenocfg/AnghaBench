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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct apr_rx_buf {int len; int /*<<< orphan*/  node; int /*<<< orphan*/  buf; } ;
struct apr {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rxwq; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int APR_HDR_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,void*,int) ; 
 struct apr* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct apr_rx_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int apr_callback(struct rpmsg_device *rpdev, void *buf,
				  int len, void *priv, u32 addr)
{
	struct apr *apr = dev_get_drvdata(&rpdev->dev);
	struct apr_rx_buf *abuf;
	unsigned long flags;

	if (len <= APR_HDR_SIZE) {
		dev_err(apr->dev, "APR: Improper apr pkt received:%p %d\n",
			buf, len);
		return -EINVAL;
	}

	abuf = kzalloc(sizeof(*abuf) + len, GFP_ATOMIC);
	if (!abuf)
		return -ENOMEM;

	abuf->len = len;
	memcpy(abuf->buf, buf, len);

	spin_lock_irqsave(&apr->rx_lock, flags);
	list_add_tail(&abuf->node, &apr->rx_list);
	spin_unlock_irqrestore(&apr->rx_lock, flags);

	queue_work(apr->rxwq, &apr->rx_work);

	return 0;
}