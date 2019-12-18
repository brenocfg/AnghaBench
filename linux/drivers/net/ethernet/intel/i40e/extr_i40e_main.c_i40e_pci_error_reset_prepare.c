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
struct pci_dev {int dummy; } ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_prep_for_reset (struct i40e_pf*,int) ; 
 struct i40e_pf* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void i40e_pci_error_reset_prepare(struct pci_dev *pdev)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);

	i40e_prep_for_reset(pf, false);
}