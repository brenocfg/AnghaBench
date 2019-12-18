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
struct ican3_dev {TYPE_1__* dpmctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  window_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int DPM_NUM_PAGES ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ican3_set_page(struct ican3_dev *mod, unsigned int page)
{
	BUG_ON(page >= DPM_NUM_PAGES);
	iowrite8(page, &mod->dpmctrl->window_address);
}