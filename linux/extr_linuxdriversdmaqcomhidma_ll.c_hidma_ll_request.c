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
typedef  int u32 ;
struct hidma_tre {int dma_sig; char const* dev_name; void (* callback ) (void*) ;unsigned int idx; int* tre_local; struct hidma_lldev* lldev; scalar_t__ err_info; scalar_t__ err_code; scalar_t__ queued; scalar_t__ status; void* data; int /*<<< orphan*/  allocated; } ;
struct hidma_lldev {int nr_tres; int chidx; struct hidma_tre* trepool; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t HIDMA_TRE_CFG_IDX ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 

int hidma_ll_request(struct hidma_lldev *lldev, u32 sig, const char *dev_name,
		     void (*callback)(void *data), void *data, u32 *tre_ch)
{
	unsigned int i;
	struct hidma_tre *tre;
	u32 *tre_local;

	if (!tre_ch || !lldev)
		return -EINVAL;

	/* need to have at least one empty spot in the queue */
	for (i = 0; i < lldev->nr_tres - 1; i++) {
		if (atomic_add_unless(&lldev->trepool[i].allocated, 1, 1))
			break;
	}

	if (i == (lldev->nr_tres - 1))
		return -ENOMEM;

	tre = &lldev->trepool[i];
	tre->dma_sig = sig;
	tre->dev_name = dev_name;
	tre->callback = callback;
	tre->data = data;
	tre->idx = i;
	tre->status = 0;
	tre->queued = 0;
	tre->err_code = 0;
	tre->err_info = 0;
	tre->lldev = lldev;
	tre_local = &tre->tre_local[0];
	tre_local[HIDMA_TRE_CFG_IDX] = (lldev->chidx & 0xFF) << 8;
	tre_local[HIDMA_TRE_CFG_IDX] |= BIT(16);	/* set IEOB */
	*tre_ch = i;
	if (callback)
		callback(data);
	return 0;
}