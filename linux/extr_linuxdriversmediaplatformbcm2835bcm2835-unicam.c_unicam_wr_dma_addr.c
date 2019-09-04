#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int sizeimage; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct unicam_device {TYPE_3__ v_fmt; int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_IBEA0 ; 
 int /*<<< orphan*/  UNICAM_IBSA0 ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  unicam_dbg (int,struct unicam_device*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void unicam_wr_dma_addr(struct unicam_device *dev, unsigned int dmaaddr)
{
	unicam_dbg(1, dev, "wr_dma_addr %08x-%08x\n",
		   dmaaddr, dmaaddr + dev->v_fmt.fmt.pix.sizeimage);
	reg_write(&dev->cfg, UNICAM_IBSA0, dmaaddr);
	reg_write(&dev->cfg, UNICAM_IBEA0,
		  dmaaddr + dev->v_fmt.fmt.pix.sizeimage);
}