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
struct bcom_ata_inc {int incr_dst; scalar_t__ incr_src; int /*<<< orphan*/  incr_bytes; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  BCOM_INITIATOR_ATA_RX ; 
 int /*<<< orphan*/  bcom_set_initiator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bcom_task_inc (int /*<<< orphan*/ ) ; 

void bcom_ata_rx_prepare(struct bcom_task *tsk)
{
	struct bcom_ata_inc *inc;

	inc = (struct bcom_ata_inc *) bcom_task_inc(tsk->tasknum);

	inc->incr_bytes	= -(s16)sizeof(u32);
	inc->incr_src	= 0;
	inc->incr_dst	= sizeof(u32);

	bcom_set_initiator(tsk->tasknum, BCOM_INITIATOR_ATA_RX);
}