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
struct tsi721_device {scalar_t__ regs; TYPE_1__* pdev; int /*<<< orphan*/  pw_fifo; int /*<<< orphan*/  pw_fifo_lock; int /*<<< orphan*/  pw_work; scalar_t__ pw_discard_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_RIO_PW_CTL ; 
 int /*<<< orphan*/  TSI721_RIO_PW_CTL_PWC_REL ; 
 int TSI721_RIO_PW_MSG_SIZE ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_pw_dpc ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int tsi721_port_write_init(struct tsi721_device *priv)
{
	priv->pw_discard_count = 0;
	INIT_WORK(&priv->pw_work, tsi721_pw_dpc);
	spin_lock_init(&priv->pw_fifo_lock);
	if (kfifo_alloc(&priv->pw_fifo,
			TSI721_RIO_PW_MSG_SIZE * 32, GFP_KERNEL)) {
		tsi_err(&priv->pdev->dev, "PW FIFO allocation failed");
		return -ENOMEM;
	}

	/* Use reliable port-write capture mode */
	iowrite32(TSI721_RIO_PW_CTL_PWC_REL, priv->regs + TSI721_RIO_PW_CTL);
	return 0;
}