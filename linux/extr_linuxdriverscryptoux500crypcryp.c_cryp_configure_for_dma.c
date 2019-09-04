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
struct cryp_device_data {TYPE_1__* base; } ;
typedef  enum cryp_dma_req_type { ____Placeholder_cryp_dma_req_type } cryp_dma_req_type ;
struct TYPE_2__ {int /*<<< orphan*/  dmacr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_SET_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cryp_configure_for_dma(struct cryp_device_data *device_data,
			    enum cryp_dma_req_type dma_req)
{
	CRYP_SET_BITS(&device_data->base->dmacr,
		      (u32) dma_req);
}