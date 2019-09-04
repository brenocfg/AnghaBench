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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_sg_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_sg_set_addr (struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_set_bpid (struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_set_final (struct dpaa2_sg_entry*,int) ; 
 int /*<<< orphan*/  dpaa2_sg_set_format (struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_set_len (struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_set_offset (struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_single ; 

__attribute__((used)) static inline void dma_to_qm_sg_one(struct dpaa2_sg_entry *qm_sg_ptr,
				    dma_addr_t dma, u32 len, u16 offset)
{
	dpaa2_sg_set_addr(qm_sg_ptr, dma);
	dpaa2_sg_set_format(qm_sg_ptr, dpaa2_sg_single);
	dpaa2_sg_set_final(qm_sg_ptr, false);
	dpaa2_sg_set_len(qm_sg_ptr, len);
	dpaa2_sg_set_bpid(qm_sg_ptr, 0);
	dpaa2_sg_set_offset(qm_sg_ptr, offset);
}