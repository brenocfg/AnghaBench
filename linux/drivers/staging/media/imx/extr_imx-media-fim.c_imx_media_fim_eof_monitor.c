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
struct imx_media_fim {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  frame_interval_monitor (struct imx_media_fim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icap_enabled (struct imx_media_fim*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void imx_media_fim_eof_monitor(struct imx_media_fim *fim, ktime_t timestamp)
{
	unsigned long flags;

	spin_lock_irqsave(&fim->lock, flags);

	if (!icap_enabled(fim))
		frame_interval_monitor(fim, timestamp);

	spin_unlock_irqrestore(&fim->lock, flags);
}