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
typedef  int u32 ;
struct TYPE_2__ {int dbid; } ;
struct ocrdma_srq {scalar_t__ db; TYPE_1__ rq; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_DB_GEN2_SRQ_OFFSET ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ocrdma_ring_srq_db(struct ocrdma_srq *srq)
{
	u32 val = srq->rq.dbid | (1 << 16);

	iowrite32(val, srq->db + OCRDMA_DB_GEN2_SRQ_OFFSET);
}