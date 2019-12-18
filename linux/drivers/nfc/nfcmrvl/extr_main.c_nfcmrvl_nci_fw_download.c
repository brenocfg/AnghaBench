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
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int nfcmrvl_fw_dnld_start (struct nci_dev*,char const*) ; 

__attribute__((used)) static int nfcmrvl_nci_fw_download(struct nci_dev *ndev,
				   const char *firmware_name)
{
	return nfcmrvl_fw_dnld_start(ndev, firmware_name);
}