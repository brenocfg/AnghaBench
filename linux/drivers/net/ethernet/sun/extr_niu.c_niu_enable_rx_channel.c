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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RXDMA_CFIG1 (int) ; 
 int RXDMA_CFIG1_EN ; 
 int RXDMA_CFIG1_QST ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int niu_enable_rx_channel(struct niu *np, int channel, int on)
{
	u64 val = nr64(RXDMA_CFIG1(channel));
	int limit;

	if (on)
		val |= RXDMA_CFIG1_EN;
	else
		val &= ~RXDMA_CFIG1_EN;
	nw64(RXDMA_CFIG1(channel), val);

	limit = 1000;
	while (--limit > 0) {
		if (nr64(RXDMA_CFIG1(channel)) & RXDMA_CFIG1_QST)
			break;
		udelay(10);
	}
	if (limit <= 0)
		return -ENODEV;
	return 0;
}