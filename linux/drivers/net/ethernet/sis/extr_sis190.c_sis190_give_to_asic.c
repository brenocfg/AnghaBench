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
struct RxDesc {int PSize; void* status; void* size; } ;

/* Variables and functions */
 int INTbit ; 
 int OWNbit ; 
 int RX_BUF_MASK ; 
 int RingEnd ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void sis190_give_to_asic(struct RxDesc *desc, u32 rx_buf_sz)
{
	u32 eor = le32_to_cpu(desc->size) & RingEnd;

	desc->PSize = 0x0;
	desc->size = cpu_to_le32((rx_buf_sz & RX_BUF_MASK) | eor);
	wmb();
	desc->status = cpu_to_le32(OWNbit | INTbit);
}