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
struct cfhsi {int /*<<< orphan*/ * qhead; } ;

/* Variables and functions */
 int CFHSI_PRIO_LAST ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cfhsi_tx_queue_len(struct cfhsi *cfhsi)
{
	int i, len = 0;
	for (i = 0; i < CFHSI_PRIO_LAST; ++i)
		len += skb_queue_len(&cfhsi->qhead[i]);
	return len;
}