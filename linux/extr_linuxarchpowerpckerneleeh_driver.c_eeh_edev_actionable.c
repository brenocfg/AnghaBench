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
struct eeh_dev {int /*<<< orphan*/  pe; scalar_t__ pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeh_dev_removed (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_pe_passed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool eeh_edev_actionable(struct eeh_dev *edev)
{
	return (edev->pdev && !eeh_dev_removed(edev) &&
		!eeh_pe_passed(edev->pe));
}