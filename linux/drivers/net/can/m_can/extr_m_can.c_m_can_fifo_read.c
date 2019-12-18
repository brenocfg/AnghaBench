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
struct TYPE_4__ {int (* read_fifo ) (struct m_can_classdev*,int) ;} ;
struct TYPE_3__ {int off; } ;

/* Variables and functions */
 size_t MRAM_RXF0 ; 
 int RXF0_ELEMENT_SIZE ; 
 int stub1 (struct m_can_classdev*,int) ; 

__attribute__((used)) static u32 m_can_fifo_read(struct m_can_classdev *cdev,
			   u32 fgi, unsigned int offset)
{
	u32 addr_offset = cdev->mcfg[MRAM_RXF0].off + fgi * RXF0_ELEMENT_SIZE +
			  offset;

	return cdev->ops->read_fifo(cdev, addr_offset);
}