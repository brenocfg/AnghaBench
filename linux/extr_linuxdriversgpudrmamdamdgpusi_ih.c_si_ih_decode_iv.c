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
typedef  int uint32_t ;
typedef  int u32 ;
struct amdgpu_iv_entry {int src_id; int* src_data; int ring_id; int vmid; int /*<<< orphan*/  client_id; } ;
struct TYPE_3__ {int rptr; int /*<<< orphan*/ * ring; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IH_CLIENTID_LEGACY ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_ih_decode_iv(struct amdgpu_device *adev,
			     struct amdgpu_iv_entry *entry)
{
	u32 ring_index = adev->irq.ih.rptr >> 2;
	uint32_t dw[4];

	dw[0] = le32_to_cpu(adev->irq.ih.ring[ring_index + 0]);
	dw[1] = le32_to_cpu(adev->irq.ih.ring[ring_index + 1]);
	dw[2] = le32_to_cpu(adev->irq.ih.ring[ring_index + 2]);
	dw[3] = le32_to_cpu(adev->irq.ih.ring[ring_index + 3]);

	entry->client_id = AMDGPU_IH_CLIENTID_LEGACY;
	entry->src_id = dw[0] & 0xff;
	entry->src_data[0] = dw[1] & 0xfffffff;
	entry->ring_id = dw[2] & 0xff;
	entry->vmid = (dw[2] >> 8) & 0xff;

	adev->irq.ih.rptr += 16;
}