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
typedef  int /*<<< orphan*/  u8 ;
struct st33zp24_dev {int /*<<< orphan*/  phy_id; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* recv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_INT_STATUS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 clear_interruption(struct st33zp24_dev *tpm_dev)
{
	u8 interrupt;

	tpm_dev->ops->recv(tpm_dev->phy_id, TPM_INT_STATUS, &interrupt, 1);
	tpm_dev->ops->send(tpm_dev->phy_id, TPM_INT_STATUS, &interrupt, 1);
	return interrupt;
}