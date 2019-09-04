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
struct cami2c {TYPE_1__* msg; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int addr; scalar_t__ len; int* buf; } ;

/* Variables and functions */
 int FCR_RFRST ; 
 int FCR_TFRST ; 
 int FIER_TEIE ; 
 int FIER_TXIE ; 
 scalar_t__ FIFO_SIZE ; 
 int /*<<< orphan*/  I2CFCR ; 
 int /*<<< orphan*/  I2CFIER ; 
 int /*<<< orphan*/  I2CFSR ; 
 int /*<<< orphan*/  I2CMAR ; 
 int /*<<< orphan*/  I2CMCR ; 
 int /*<<< orphan*/  I2CMIER ; 
 int /*<<< orphan*/  I2CMSR ; 
 int /*<<< orphan*/  I2CRXTX ; 
 int /*<<< orphan*/  I2CSAR ; 
 int /*<<< orphan*/  I2CTFDR ; 
 int /*<<< orphan*/  IDF_SEND ; 
 scalar_t__ IN32 (struct cami2c*,int /*<<< orphan*/ ) ; 
 int MCR_ESG ; 
 int MCR_MIE ; 
 int MIE_MALE ; 
 int MIE_MATE ; 
 int MIE_MNRE ; 
 int MIE_MSTE ; 
 int /*<<< orphan*/  OUT32 (struct cami2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh7760_i2c_msend(struct cami2c *id)
{
	int len;

	id->flags |= IDF_SEND;

	/* set the slave addr reg; otherwise xmit wont work! */
	OUT32(id, I2CSAR, 0xfe);
	OUT32(id, I2CMAR, (id->msg->addr << 1) | 0);

	/* adjust tx fifo trigger */
	if (id->msg->len >= FIFO_SIZE)
		len = 2;	/* trig: 2 bytes left in TX fifo */
	else
		len = 0;	/* trig: 8 bytes left in TX fifo */

	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFCR, FCR_RFRST | ((len & 3) << 2));

	while (id->msg->len && IN32(id, I2CTFDR) < FIFO_SIZE) {
		OUT32(id, I2CRXTX, *(id->msg->buf));
		(id->msg->len)--;
		(id->msg->buf)++;
	}

	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMCR, MCR_MIE | MCR_ESG);
	OUT32(id, I2CFSR, 0);
	OUT32(id, I2CMIER, MIE_MNRE | MIE_MALE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIER, FIER_TEIE | (id->msg->len ? FIER_TXIE : 0));
}