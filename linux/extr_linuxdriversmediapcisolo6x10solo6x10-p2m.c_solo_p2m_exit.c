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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_IRQ_P2M (int) ; 
 int SOLO_NR_P2M ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 

void solo_p2m_exit(struct solo_dev *solo_dev)
{
	int i;

	for (i = 0; i < SOLO_NR_P2M; i++)
		solo_irq_off(solo_dev, SOLO_IRQ_P2M(i));
}