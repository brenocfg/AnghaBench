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
struct spu {unsigned long class_0_pending; int /*<<< orphan*/  register_lock; scalar_t__ class_0_dar; int /*<<< orphan*/  (* stop_callback ) (struct spu*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long spu_int_mask_get (struct spu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_int_stat_clear (struct spu*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long spu_int_stat_get (struct spu*,int /*<<< orphan*/ ) ; 
 scalar_t__ spu_mfc_dar_get (struct spu*) ; 
 int /*<<< orphan*/  stub1 (struct spu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
spu_irq_class_0(int irq, void *data)
{
	struct spu *spu;
	unsigned long stat, mask;

	spu = data;

	spin_lock(&spu->register_lock);
	mask = spu_int_mask_get(spu, 0);
	stat = spu_int_stat_get(spu, 0) & mask;

	spu->class_0_pending |= stat;
	spu->class_0_dar = spu_mfc_dar_get(spu);
	spu->stop_callback(spu, 0);
	spu->class_0_pending = 0;
	spu->class_0_dar = 0;

	spu_int_stat_clear(spu, 0, stat);
	spin_unlock(&spu->register_lock);

	return IRQ_HANDLED;
}