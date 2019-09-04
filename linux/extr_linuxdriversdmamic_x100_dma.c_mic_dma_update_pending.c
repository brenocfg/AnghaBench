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
struct mic_dma_chan {int /*<<< orphan*/  api_ch; int /*<<< orphan*/  submitted; int /*<<< orphan*/  issued; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_dma_issue_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ mic_dma_pending_level ; 
 scalar_t__ mic_dma_ring_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mic_dma_update_pending(struct mic_dma_chan *ch)
{
	if (mic_dma_ring_count(ch->issued, ch->submitted)
			> mic_dma_pending_level)
		mic_dma_issue_pending(&ch->api_ch);
}