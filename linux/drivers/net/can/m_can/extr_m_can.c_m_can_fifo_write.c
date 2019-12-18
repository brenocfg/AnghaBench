#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct m_can_classdev {TYPE_2__* ops; TYPE_1__* mcfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_fifo ) (struct m_can_classdev*,int,int) ;} ;
struct TYPE_3__ {int off; } ;

/* Variables and functions */
 size_t MRAM_TXB ; 
 int TXB_ELEMENT_SIZE ; 
 int /*<<< orphan*/  stub1 (struct m_can_classdev*,int,int) ; 

__attribute__((used)) static void m_can_fifo_write(struct m_can_classdev *cdev,
			     u32 fpi, unsigned int offset, u32 val)
{
	u32 addr_offset = cdev->mcfg[MRAM_TXB].off + fpi * TXB_ELEMENT_SIZE +
			  offset;

	cdev->ops->write_fifo(cdev, addr_offset, val);
}