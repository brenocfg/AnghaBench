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
typedef  int u32 ;
struct slic_stats {int dummy; } ;
struct slic_device {struct slic_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_INC_STATS_COUNTER (struct slic_stats*,int /*<<< orphan*/ ) ; 
 int SLIC_ISR_RMISS ; 
 int SLIC_ISR_XDROP ; 
 int /*<<< orphan*/  irq_errs ; 
 int /*<<< orphan*/  rx_buff_miss ; 
 int /*<<< orphan*/  tx_dropped ; 

__attribute__((used)) static void slic_handle_err_irq(struct slic_device *sdev, u32 isr)
{
	struct slic_stats *stats = &sdev->stats;

	if (isr & SLIC_ISR_RMISS)
		SLIC_INC_STATS_COUNTER(stats, rx_buff_miss);
	if (isr & SLIC_ISR_XDROP)
		SLIC_INC_STATS_COUNTER(stats, tx_dropped);
	if (!(isr & (SLIC_ISR_RMISS | SLIC_ISR_XDROP)))
		SLIC_INC_STATS_COUNTER(stats, irq_errs);
}