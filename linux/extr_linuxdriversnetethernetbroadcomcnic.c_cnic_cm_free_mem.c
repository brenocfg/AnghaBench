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
struct cnic_local {int /*<<< orphan*/  csk_port_tbl; int /*<<< orphan*/ * csk_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cnic_free_id_tbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_cm_free_mem(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;

	kvfree(cp->csk_tbl);
	cp->csk_tbl = NULL;
	cnic_free_id_tbl(&cp->csk_port_tbl);
}