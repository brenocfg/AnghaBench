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
struct sn_irq_info {int dummy; } ;
typedef  int nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __pa (struct sn_irq_info*) ; 
 int /*<<< orphan*/  kfree (struct sn_irq_info*) ; 
 struct sn_irq_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tiocx_intr_alloc (int,int,int /*<<< orphan*/ ,int,int,int) ; 

struct sn_irq_info *tiocx_irq_alloc(nasid_t nasid, int widget, int irq,
				    nasid_t req_nasid, int slice)
{
	struct sn_irq_info *sn_irq_info;
	int status;
	int sn_irq_size = sizeof(struct sn_irq_info);

	if ((nasid & 1) == 0)
		return NULL;

	sn_irq_info = kzalloc(sn_irq_size, GFP_KERNEL);
	if (sn_irq_info == NULL)
		return NULL;

	status = tiocx_intr_alloc(nasid, widget, __pa(sn_irq_info), irq,
				  req_nasid, slice);
	if (status) {
		kfree(sn_irq_info);
		return NULL;
	} else {
		return sn_irq_info;
	}
}