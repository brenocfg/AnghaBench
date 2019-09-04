#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_dle_dma; TYPE_2__ rx_dle_q; TYPE_1__* pci; int /*<<< orphan*/  rx_open; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_3__ IADEV ;

/* Variables and functions */
 int /*<<< orphan*/  DLE_TOTAL_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ia_free_rx(IADEV *iadev)
{
	kfree(iadev->rx_open);
	dma_free_coherent(&iadev->pci->dev, DLE_TOTAL_SIZE, iadev->rx_dle_q.start,
			  iadev->rx_dle_dma);
}