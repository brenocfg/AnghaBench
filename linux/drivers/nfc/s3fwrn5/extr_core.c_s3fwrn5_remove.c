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
struct s3fwrn5_info {int dummy; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3FWRN5_MODE_COLD ; 
 int /*<<< orphan*/  nci_free_device (struct nci_dev*) ; 
 struct s3fwrn5_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_unregister_device (struct nci_dev*) ; 
 int /*<<< orphan*/  s3fwrn5_set_mode (struct s3fwrn5_info*,int /*<<< orphan*/ ) ; 

void s3fwrn5_remove(struct nci_dev *ndev)
{
	struct s3fwrn5_info *info = nci_get_drvdata(ndev);

	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);

	nci_unregister_device(ndev);
	nci_free_device(ndev);
}