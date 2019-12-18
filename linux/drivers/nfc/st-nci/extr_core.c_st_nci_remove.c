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
struct st_nci_info {int /*<<< orphan*/  ndlc; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nci_free_device (struct nci_dev*) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_unregister_device (struct nci_dev*) ; 
 int /*<<< orphan*/  ndlc_close (int /*<<< orphan*/ ) ; 

void st_nci_remove(struct nci_dev *ndev)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	ndlc_close(info->ndlc);

	nci_unregister_device(ndev);
	nci_free_device(ndev);
}