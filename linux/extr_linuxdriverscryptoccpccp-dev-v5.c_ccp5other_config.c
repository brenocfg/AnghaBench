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
typedef  int u32 ;
struct ccp_device {scalar_t__ io_regs; } ;

/* Variables and functions */
 scalar_t__ CMD5_AES_MASK_OFFSET ; 
 scalar_t__ CMD5_CLK_GATE_CTL_OFFSET ; 
 scalar_t__ CMD5_CMD_TIMEOUT_OFFSET ; 
 scalar_t__ CMD5_CONFIG_0_OFFSET ; 
 scalar_t__ CMD5_QUEUE_MASK_OFFSET ; 
 scalar_t__ CMD5_QUEUE_PRIO_OFFSET ; 
 scalar_t__ CMD5_TRNG_CTL_OFFSET ; 
 scalar_t__ LSB_PRIVATE_MASK_HI_OFFSET ; 
 scalar_t__ LSB_PRIVATE_MASK_LO_OFFSET ; 
 scalar_t__ TRNG_OUT_REG ; 
 int /*<<< orphan*/  ccp5_config (struct ccp_device*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ccp5other_config(struct ccp_device *ccp)
{
	int i;
	u32 rnd;

	/* We own all of the queues on the NTB CCP */

	iowrite32(0x00012D57, ccp->io_regs + CMD5_TRNG_CTL_OFFSET);
	iowrite32(0x00000003, ccp->io_regs + CMD5_CONFIG_0_OFFSET);
	for (i = 0; i < 12; i++) {
		rnd = ioread32(ccp->io_regs + TRNG_OUT_REG);
		iowrite32(rnd, ccp->io_regs + CMD5_AES_MASK_OFFSET);
	}

	iowrite32(0x0000001F, ccp->io_regs + CMD5_QUEUE_MASK_OFFSET);
	iowrite32(0x00005B6D, ccp->io_regs + CMD5_QUEUE_PRIO_OFFSET);
	iowrite32(0x00000000, ccp->io_regs + CMD5_CMD_TIMEOUT_OFFSET);

	iowrite32(0x3FFFFFFF, ccp->io_regs + LSB_PRIVATE_MASK_LO_OFFSET);
	iowrite32(0x000003FF, ccp->io_regs + LSB_PRIVATE_MASK_HI_OFFSET);

	iowrite32(0x00108823, ccp->io_regs + CMD5_CLK_GATE_CTL_OFFSET);

	ccp5_config(ccp);
}