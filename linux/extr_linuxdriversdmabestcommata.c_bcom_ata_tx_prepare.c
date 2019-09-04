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
struct bcom_task {int /*<<< orphan*/  tasknum; } ;
struct bcom_ata_inc {int incr_src; scalar_t__ incr_dst; int /*<<< orphan*/  incr_bytes; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  BCOM_INITIATOR_ATA_TX ; 
 int /*<<< orphan*/  bcom_set_initiator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bcom_task_inc (int /*<<< orphan*/ ) ; 

void bcom_ata_tx_prepare(struct bcom_task *tsk)
{
	struct bcom_ata_inc *inc;

	inc = (struct bcom_ata_inc *) bcom_task_inc(tsk->tasknum);

	inc->incr_bytes	= -(s16)sizeof(u32);
	inc->incr_src	= sizeof(u32);
	inc->incr_dst	= 0;

	bcom_set_initiator(tsk->tasknum, BCOM_INITIATOR_ATA_TX);
}