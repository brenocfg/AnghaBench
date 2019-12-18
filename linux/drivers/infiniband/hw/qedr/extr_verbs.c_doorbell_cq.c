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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  agg_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; TYPE_1__ data; } ;
struct qedr_cq {int /*<<< orphan*/  db_addr; TYPE_2__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doorbell_cq(struct qedr_cq *cq, u32 cons, u8 flags)
{
	cq->db.data.agg_flags = flags;
	cq->db.data.value = cpu_to_le32(cons);
	writeq(cq->db.raw, cq->db_addr);
}