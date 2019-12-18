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
struct st_nci_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndlc; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_NCI_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  ndlc_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_nci_close(struct nci_dev *ndev)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	if (!test_bit(ST_NCI_RUNNING, &info->flags))
		return 0;

	ndlc_close(info->ndlc);

	clear_bit(ST_NCI_RUNNING, &info->flags);

	return 0;
}