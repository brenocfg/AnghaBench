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
struct sh_mobile_i2c_data {int iccl; int icch; int pos; scalar_t__ dma_buf; struct i2c_msg* msg; scalar_t__ sr; } ;
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCH ; 
 int /*<<< orphan*/  ICCL ; 
 int /*<<< orphan*/  ICCR ; 
 int ICCR_ICE ; 
 int ICCR_SCP ; 
 int /*<<< orphan*/  ICIC ; 
 int ICIC_ALE ; 
 int ICIC_DTEE ; 
 int ICIC_TACKE ; 
 int ICIC_WAITE ; 
 scalar_t__ i2c_get_dma_safe_msg_buf (struct i2c_msg*,int) ; 
 int /*<<< orphan*/  iic_wr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_mobile_i2c_xfer_dma (struct sh_mobile_i2c_data*) ; 

__attribute__((used)) static void start_ch(struct sh_mobile_i2c_data *pd, struct i2c_msg *usr_msg,
		     bool do_init)
{
	if (do_init) {
		/* Initialize channel registers */
		iic_wr(pd, ICCR, ICCR_SCP);

		/* Enable channel and configure rx ack */
		iic_wr(pd, ICCR, ICCR_ICE | ICCR_SCP);

		/* Set the clock */
		iic_wr(pd, ICCL, pd->iccl & 0xff);
		iic_wr(pd, ICCH, pd->icch & 0xff);
	}

	pd->msg = usr_msg;
	pd->pos = -1;
	pd->sr = 0;

	pd->dma_buf = i2c_get_dma_safe_msg_buf(pd->msg, 8);
	if (pd->dma_buf)
		sh_mobile_i2c_xfer_dma(pd);

	/* Enable all interrupts to begin with */
	iic_wr(pd, ICIC, ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE);
}