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
struct m_can_classdev {TYPE_1__* mcfg; } ;
struct TYPE_2__ {int off; int num; } ;

/* Variables and functions */
 size_t MRAM_SIDF ; 
 size_t MRAM_TXB ; 
 int TXB_ELEMENT_SIZE ; 
 int /*<<< orphan*/  m_can_fifo_write_no_off (struct m_can_classdev*,int,int) ; 

void m_can_init_ram(struct m_can_classdev *cdev)
{
	int end, i, start;

	/* initialize the entire Message RAM in use to avoid possible
	 * ECC/parity checksum errors when reading an uninitialized buffer
	 */
	start = cdev->mcfg[MRAM_SIDF].off;
	end = cdev->mcfg[MRAM_TXB].off +
		cdev->mcfg[MRAM_TXB].num * TXB_ELEMENT_SIZE;

	for (i = start; i < end; i += 4)
		m_can_fifo_write_no_off(cdev, i, 0x0);
}