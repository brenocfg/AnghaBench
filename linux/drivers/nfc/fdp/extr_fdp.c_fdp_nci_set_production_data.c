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
typedef  int /*<<< orphan*/  u8 ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_PROP_SET_PDATA_OID ; 
 int nci_prop_cmd (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int fdp_nci_set_production_data(struct nci_dev *ndev, u8 len,
					      char *data)
{
	return nci_prop_cmd(ndev, NCI_OP_PROP_SET_PDATA_OID, len, data);
}