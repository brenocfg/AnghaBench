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
struct wcn36xx_hal_tx_compl_ind_msg {int /*<<< orphan*/  status; } ;
struct wcn36xx {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  wcn36xx_dxe_tx_ack_ind (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

__attribute__((used)) static int wcn36xx_smd_tx_compl_ind(struct wcn36xx *wcn, void *buf, size_t len)
{
	struct wcn36xx_hal_tx_compl_ind_msg *rsp = buf;

	if (len != sizeof(*rsp)) {
		wcn36xx_warn("Bad TX complete indication\n");
		return -EIO;
	}

	wcn36xx_dxe_tx_ack_ind(wcn, rsp->status);

	return 0;
}