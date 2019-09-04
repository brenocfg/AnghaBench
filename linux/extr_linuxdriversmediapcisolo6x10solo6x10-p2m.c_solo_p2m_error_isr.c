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
struct solo_p2m_dev {int error; int /*<<< orphan*/  completion; } ;
struct solo_dev {struct solo_p2m_dev* p2m_dev; } ;

/* Variables and functions */
 int SOLO_NR_P2M ; 
 int /*<<< orphan*/  SOLO_P2M_CONTROL (int) ; 
 int /*<<< orphan*/  SOLO_PCI_ERR ; 
 unsigned int SOLO_PCI_ERR_P2M ; 
 unsigned int SOLO_PCI_ERR_P2M_DESC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void solo_p2m_error_isr(struct solo_dev *solo_dev)
{
	unsigned int err = solo_reg_read(solo_dev, SOLO_PCI_ERR);
	struct solo_p2m_dev *p2m_dev;
	int i;

	if (!(err & (SOLO_PCI_ERR_P2M | SOLO_PCI_ERR_P2M_DESC)))
		return;

	for (i = 0; i < SOLO_NR_P2M; i++) {
		p2m_dev = &solo_dev->p2m_dev[i];
		p2m_dev->error = 1;
		solo_reg_write(solo_dev, SOLO_P2M_CONTROL(i), 0);
		complete(&p2m_dev->completion);
	}
}