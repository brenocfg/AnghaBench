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
struct nci_driver_ops {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct nci_driver_ops*) ; 
 struct nci_driver_ops* s3fwrn5_nci_prop_ops ; 

void s3fwrn5_nci_get_prop_ops(struct nci_driver_ops **ops, size_t *n)
{
	*ops = s3fwrn5_nci_prop_ops;
	*n = ARRAY_SIZE(s3fwrn5_nci_prop_ops);
}