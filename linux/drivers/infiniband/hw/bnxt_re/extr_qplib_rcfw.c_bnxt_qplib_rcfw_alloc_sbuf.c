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
typedef  int /*<<< orphan*/  u32 ;
struct bnxt_qplib_rcfw_sbuf {int /*<<< orphan*/  sb; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct bnxt_qplib_rcfw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bnxt_qplib_rcfw_sbuf*) ; 
 struct bnxt_qplib_rcfw_sbuf* kzalloc (int,int /*<<< orphan*/ ) ; 

struct bnxt_qplib_rcfw_sbuf *bnxt_qplib_rcfw_alloc_sbuf(
		struct bnxt_qplib_rcfw *rcfw,
		u32 size)
{
	struct bnxt_qplib_rcfw_sbuf *sbuf;

	sbuf = kzalloc(sizeof(*sbuf), GFP_ATOMIC);
	if (!sbuf)
		return NULL;

	sbuf->size = size;
	sbuf->sb = dma_alloc_coherent(&rcfw->pdev->dev, sbuf->size,
				      &sbuf->dma_addr, GFP_ATOMIC);
	if (!sbuf->sb)
		goto bail;

	return sbuf;
bail:
	kfree(sbuf);
	return NULL;
}