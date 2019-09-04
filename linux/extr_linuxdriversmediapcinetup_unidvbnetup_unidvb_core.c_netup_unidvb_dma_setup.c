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
struct netup_unidvb_dev {int /*<<< orphan*/ * dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  netup_unidvb_dma_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netup_unidvb_dma_fini (struct netup_unidvb_dev*,int /*<<< orphan*/ ) ; 
 int netup_unidvb_dma_init (struct netup_unidvb_dev*,int) ; 

__attribute__((used)) static int netup_unidvb_dma_setup(struct netup_unidvb_dev *ndev)
{
	int res;

	res = netup_unidvb_dma_init(ndev, 0);
	if (res)
		return res;
	res = netup_unidvb_dma_init(ndev, 1);
	if (res) {
		netup_unidvb_dma_fini(ndev, 0);
		return res;
	}
	netup_unidvb_dma_enable(&ndev->dma[0], 0);
	netup_unidvb_dma_enable(&ndev->dma[1], 0);
	return 0;
}