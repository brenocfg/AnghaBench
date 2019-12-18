#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qed_iwarp_ll2_buff {int buff_size; int /*<<< orphan*/  data; int /*<<< orphan*/  data_phys_addr; } ;
struct qed_hwfn {TYPE_2__* cdev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_iwarp_ll2_buff*) ; 
 struct qed_iwarp_ll2_buff* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qed_iwarp_ll2_post_rx (struct qed_hwfn*,struct qed_iwarp_ll2_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qed_iwarp_ll2_alloc_buffers(struct qed_hwfn *p_hwfn,
			    int num_rx_bufs, int buff_size, u8 ll2_handle)
{
	struct qed_iwarp_ll2_buff *buffer;
	int rc = 0;
	int i;

	for (i = 0; i < num_rx_bufs; i++) {
		buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
		if (!buffer) {
			rc = -ENOMEM;
			break;
		}

		buffer->data = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
						  buff_size,
						  &buffer->data_phys_addr,
						  GFP_KERNEL);
		if (!buffer->data) {
			kfree(buffer);
			rc = -ENOMEM;
			break;
		}

		buffer->buff_size = buff_size;
		rc = qed_iwarp_ll2_post_rx(p_hwfn, buffer, ll2_handle);
		if (rc)
			/* buffers will be deallocated by qed_ll2 */
			break;
	}
	return rc;
}