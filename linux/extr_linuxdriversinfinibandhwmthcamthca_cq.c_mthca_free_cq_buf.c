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
struct mthca_dev {int dummy; } ;
struct mthca_cq_buf {int /*<<< orphan*/  mr; int /*<<< orphan*/  is_direct; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int MTHCA_CQ_ENTRY_SIZE ; 
 int /*<<< orphan*/  mthca_buf_free (struct mthca_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mthca_free_cq_buf(struct mthca_dev *dev, struct mthca_cq_buf *buf, int cqe)
{
	mthca_buf_free(dev, (cqe + 1) * MTHCA_CQ_ENTRY_SIZE, &buf->queue,
		       buf->is_direct, &buf->mr);
}