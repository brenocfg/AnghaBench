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
typedef  int /*<<< orphan*/  u64 ;
struct vio_dev {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_SEND_CRQ ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvtpm_send_crq_word(struct vio_dev *vdev, u64 w1)
{
	return plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, w1, 0);
}