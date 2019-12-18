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
struct ns83820 {scalar_t__ base; int /*<<< orphan*/  tx_free_idx; int /*<<< orphan*/  tx_idx; } ;

/* Variables and functions */
 scalar_t__ CR ; 
 int /*<<< orphan*/  CR_TXE ; 
 int /*<<< orphan*/  dprintk (char*,struct ns83820*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void kick_tx(struct ns83820 *dev)
{
	dprintk("kick_tx(%p): tx_idx=%d free_idx=%d\n",
		dev, dev->tx_idx, dev->tx_free_idx);
	writel(CR_TXE, dev->base + CR);
}