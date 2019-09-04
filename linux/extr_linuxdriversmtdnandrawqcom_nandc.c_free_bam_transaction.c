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
struct qcom_nand_controller {int /*<<< orphan*/  dev; struct bam_transaction* bam_txn; } ;
struct bam_transaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct bam_transaction*) ; 

__attribute__((used)) static void free_bam_transaction(struct qcom_nand_controller *nandc)
{
	struct bam_transaction *bam_txn = nandc->bam_txn;

	devm_kfree(nandc->dev, bam_txn);
}