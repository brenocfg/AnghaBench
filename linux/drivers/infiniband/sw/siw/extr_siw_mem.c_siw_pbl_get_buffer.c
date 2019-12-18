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
typedef  scalar_t__ u64 ;
struct siw_pble {scalar_t__ pbl_off; scalar_t__ size; scalar_t__ addr; } ;
struct siw_pbl {int num_buf; struct siw_pble* pbe; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

dma_addr_t siw_pbl_get_buffer(struct siw_pbl *pbl, u64 off, int *len, int *idx)
{
	int i = idx ? *idx : 0;

	while (i < pbl->num_buf) {
		struct siw_pble *pble = &pbl->pbe[i];

		if (pble->pbl_off + pble->size > off) {
			u64 pble_off = off - pble->pbl_off;

			if (len)
				*len = pble->size - pble_off;
			if (idx)
				*idx = i;

			return pble->addr + pble_off;
		}
		i++;
	}
	if (len)
		*len = 0;
	return 0;
}