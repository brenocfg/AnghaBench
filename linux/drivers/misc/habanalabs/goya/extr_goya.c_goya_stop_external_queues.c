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
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int goya_stop_queue (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDMA_QM_0_CP_STS ; 
 int /*<<< orphan*/  mmDMA_QM_0_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_0_GLBL_STS0 ; 
 int /*<<< orphan*/  mmDMA_QM_1_CP_STS ; 
 int /*<<< orphan*/  mmDMA_QM_1_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_1_GLBL_STS0 ; 
 int /*<<< orphan*/  mmDMA_QM_2_CP_STS ; 
 int /*<<< orphan*/  mmDMA_QM_2_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_2_GLBL_STS0 ; 
 int /*<<< orphan*/  mmDMA_QM_3_CP_STS ; 
 int /*<<< orphan*/  mmDMA_QM_3_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_3_GLBL_STS0 ; 
 int /*<<< orphan*/  mmDMA_QM_4_CP_STS ; 
 int /*<<< orphan*/  mmDMA_QM_4_GLBL_CFG1 ; 
 int /*<<< orphan*/  mmDMA_QM_4_GLBL_STS0 ; 

__attribute__((used)) static int goya_stop_external_queues(struct hl_device *hdev)
{
	int rc, retval = 0;

	rc = goya_stop_queue(hdev,
			mmDMA_QM_0_GLBL_CFG1,
			mmDMA_QM_0_CP_STS,
			mmDMA_QM_0_GLBL_STS0);

	if (rc) {
		dev_err(hdev->dev, "failed to stop DMA QMAN 0\n");
		retval = -EIO;
	}

	rc = goya_stop_queue(hdev,
			mmDMA_QM_1_GLBL_CFG1,
			mmDMA_QM_1_CP_STS,
			mmDMA_QM_1_GLBL_STS0);

	if (rc) {
		dev_err(hdev->dev, "failed to stop DMA QMAN 1\n");
		retval = -EIO;
	}

	rc = goya_stop_queue(hdev,
			mmDMA_QM_2_GLBL_CFG1,
			mmDMA_QM_2_CP_STS,
			mmDMA_QM_2_GLBL_STS0);

	if (rc) {
		dev_err(hdev->dev, "failed to stop DMA QMAN 2\n");
		retval = -EIO;
	}

	rc = goya_stop_queue(hdev,
			mmDMA_QM_3_GLBL_CFG1,
			mmDMA_QM_3_CP_STS,
			mmDMA_QM_3_GLBL_STS0);

	if (rc) {
		dev_err(hdev->dev, "failed to stop DMA QMAN 3\n");
		retval = -EIO;
	}

	rc = goya_stop_queue(hdev,
			mmDMA_QM_4_GLBL_CFG1,
			mmDMA_QM_4_CP_STS,
			mmDMA_QM_4_GLBL_STS0);

	if (rc) {
		dev_err(hdev->dev, "failed to stop DMA QMAN 4\n");
		retval = -EIO;
	}

	return retval;
}