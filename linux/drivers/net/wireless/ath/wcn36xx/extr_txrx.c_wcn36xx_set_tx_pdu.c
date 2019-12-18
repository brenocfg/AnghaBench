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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int mpdu_header_off; int /*<<< orphan*/  bd_ssn; int /*<<< orphan*/  tid; void* mpdu_len; void* mpdu_header_len; void* mpdu_data_off; } ;
struct wcn36xx_tx_bd {TYPE_1__ pdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_TXBD_SSN_FILL_DPU_QOS ; 

__attribute__((used)) static void wcn36xx_set_tx_pdu(struct wcn36xx_tx_bd *bd,
			       u32 mpdu_header_len,
			       u32 len,
			       u16 tid)
{
	bd->pdu.mpdu_header_len = mpdu_header_len;
	bd->pdu.mpdu_header_off = sizeof(*bd);
	bd->pdu.mpdu_data_off = bd->pdu.mpdu_header_len +
		bd->pdu.mpdu_header_off;
	bd->pdu.mpdu_len = len;
	bd->pdu.tid = tid;
	bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FILL_DPU_QOS;
}