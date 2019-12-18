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
typedef  int /*<<< orphan*/  u32 ;
struct cnic_sock {int dummy; } ;
struct cnic_local {int /*<<< orphan*/  csk_port_tbl; TYPE_1__* csk_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_LOCAL_PORT_MIN ; 
 int /*<<< orphan*/  CNIC_LOCAL_PORT_RANGE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_CM_SK_TBL_SZ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_cm_free_mem (struct cnic_dev*) ; 
 scalar_t__ cnic_init_id_tbl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_u32 () ; 

__attribute__((used)) static int cnic_cm_alloc_mem(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	u32 port_id;
	int i;

	cp->csk_tbl = kvcalloc(MAX_CM_SK_TBL_SZ, sizeof(struct cnic_sock),
			       GFP_KERNEL);
	if (!cp->csk_tbl)
		return -ENOMEM;

	for (i = 0; i < MAX_CM_SK_TBL_SZ; i++)
		atomic_set(&cp->csk_tbl[i].ref_count, 0);

	port_id = prandom_u32();
	port_id %= CNIC_LOCAL_PORT_RANGE;
	if (cnic_init_id_tbl(&cp->csk_port_tbl, CNIC_LOCAL_PORT_RANGE,
			     CNIC_LOCAL_PORT_MIN, port_id)) {
		cnic_cm_free_mem(dev);
		return -ENOMEM;
	}
	return 0;
}