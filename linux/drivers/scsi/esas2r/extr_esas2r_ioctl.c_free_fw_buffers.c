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
struct TYPE_4__ {int /*<<< orphan*/ * data; scalar_t__ phys; scalar_t__ orig_len; } ;
struct esas2r_adapter {TYPE_2__ firmware; TYPE_1__* pcid; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_fw_buffers(struct esas2r_adapter *a)
{
	if (a->firmware.data) {
		dma_free_coherent(&a->pcid->dev,
				  (size_t)a->firmware.orig_len,
				  a->firmware.data,
				  (dma_addr_t)a->firmware.phys);

		a->firmware.data = NULL;
	}
}