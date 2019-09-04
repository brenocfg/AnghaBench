#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnxt_qplib_rcfw_sbuf {int /*<<< orphan*/  dma_addr; scalar_t__ sb; int /*<<< orphan*/  size; } ;
struct bnxt_qplib_rcfw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bnxt_qplib_rcfw_sbuf*) ; 

void bnxt_qplib_rcfw_free_sbuf(struct bnxt_qplib_rcfw *rcfw,
			       struct bnxt_qplib_rcfw_sbuf *sbuf)
{
	if (sbuf->sb)
		dma_free_coherent(&rcfw->pdev->dev, sbuf->size,
				  sbuf->sb, sbuf->dma_addr);
	kfree(sbuf);
}