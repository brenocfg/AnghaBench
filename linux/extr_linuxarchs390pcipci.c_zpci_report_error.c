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
struct zpci_report_error_header {int dummy; } ;
struct zpci_dev {int /*<<< orphan*/  fid; int /*<<< orphan*/  fh; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int sclp_pci_report (struct zpci_report_error_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zpci_dev* to_zpci (struct pci_dev*) ; 

int zpci_report_error(struct pci_dev *pdev,
		      struct zpci_report_error_header *report)
{
	struct zpci_dev *zdev = to_zpci(pdev);

	return sclp_pci_report(report, zdev->fh, zdev->fid);
}