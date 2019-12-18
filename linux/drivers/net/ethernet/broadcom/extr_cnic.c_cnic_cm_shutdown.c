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
struct cnic_sock {int /*<<< orphan*/  flags; } ;
struct cnic_local {struct cnic_sock* csk_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int MAX_CM_SK_TBL_SZ ; 
 int /*<<< orphan*/  SK_F_INUSE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_cm_cleanup (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_cm_free_mem (struct cnic_dev*) ; 

__attribute__((used)) static int cnic_cm_shutdown(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	int i;

	if (!cp->csk_tbl)
		return 0;

	for (i = 0; i < MAX_CM_SK_TBL_SZ; i++) {
		struct cnic_sock *csk = &cp->csk_tbl[i];

		clear_bit(SK_F_INUSE, &csk->flags);
		cnic_cm_cleanup(csk);
	}
	cnic_cm_free_mem(dev);

	return 0;
}