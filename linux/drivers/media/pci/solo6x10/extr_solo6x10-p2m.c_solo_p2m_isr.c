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
struct solo_p2m_dev {size_t desc_count; size_t desc_idx; struct solo_p2m_desc* descs; int /*<<< orphan*/  completion; } ;
struct solo_p2m_desc {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  cfg; int /*<<< orphan*/  ext_addr; int /*<<< orphan*/  dma_addr; } ;
struct solo_dev {struct solo_p2m_dev* p2m_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_P2M_CONTROL (int) ; 
 int /*<<< orphan*/  SOLO_P2M_EXT_ADR (int) ; 
 int /*<<< orphan*/  SOLO_P2M_EXT_CFG (int) ; 
 int /*<<< orphan*/  SOLO_P2M_TAR_ADR (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void solo_p2m_isr(struct solo_dev *solo_dev, int id)
{
	struct solo_p2m_dev *p2m_dev = &solo_dev->p2m_dev[id];
	struct solo_p2m_desc *desc;

	if (p2m_dev->desc_count <= p2m_dev->desc_idx) {
		complete(&p2m_dev->completion);
		return;
	}

	/* Setup next descriptor */
	p2m_dev->desc_idx++;
	desc = &p2m_dev->descs[p2m_dev->desc_idx];

	solo_reg_write(solo_dev, SOLO_P2M_CONTROL(id), 0);
	solo_reg_write(solo_dev, SOLO_P2M_TAR_ADR(id), desc->dma_addr);
	solo_reg_write(solo_dev, SOLO_P2M_EXT_ADR(id), desc->ext_addr);
	solo_reg_write(solo_dev, SOLO_P2M_EXT_CFG(id), desc->cfg);
	solo_reg_write(solo_dev, SOLO_P2M_CONTROL(id), desc->ctrl);
}