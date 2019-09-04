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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct ioat_raw_descriptor {scalar_t__* field; } ;
struct ioat_pq_descriptor {void** coef; } ;
struct ioat_pq16a_descriptor {void** coef; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t* pq16_idx_to_desc ; 
 size_t* pq16_idx_to_field ; 

__attribute__((used)) static void pq16_set_src(struct ioat_raw_descriptor *desc[3],
			dma_addr_t addr, u32 offset, u8 coef, unsigned idx)
{
	struct ioat_pq_descriptor *pq = (struct ioat_pq_descriptor *)desc[0];
	struct ioat_pq16a_descriptor *pq16 =
		(struct ioat_pq16a_descriptor *)desc[1];
	struct ioat_raw_descriptor *raw = desc[pq16_idx_to_desc[idx]];

	raw->field[pq16_idx_to_field[idx]] = addr + offset;

	if (idx < 8)
		pq->coef[idx] = coef;
	else
		pq16->coef[idx - 8] = coef;
}