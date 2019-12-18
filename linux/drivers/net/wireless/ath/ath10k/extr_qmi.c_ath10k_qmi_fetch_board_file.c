#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  board_id; } ;
struct ath10k_qmi {struct ath10k* ar; TYPE_3__ board_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  dir; } ;
struct TYPE_9__ {TYPE_5__ fw; } ;
struct TYPE_7__ {int qmi_ids_valid; int /*<<< orphan*/  qmi_board_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;
struct ath10k {TYPE_4__ hw_params; TYPE_2__ id; TYPE_1__ hif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_BD_IE_BOARD ; 
 int /*<<< orphan*/  ATH10K_BUS_SNOC ; 
 int /*<<< orphan*/  WCN3990_HW_1_0_FW_DIR ; 
 int ath10k_core_fetch_board_file (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_qmi_fetch_board_file(struct ath10k_qmi *qmi)
{
	struct ath10k *ar = qmi->ar;

	ar->hif.bus = ATH10K_BUS_SNOC;
	ar->id.qmi_ids_valid = true;
	ar->id.qmi_board_id = qmi->board_info.board_id;
	ar->hw_params.fw.dir = WCN3990_HW_1_0_FW_DIR;

	return ath10k_core_fetch_board_file(qmi->ar, ATH10K_BD_IE_BOARD);
}