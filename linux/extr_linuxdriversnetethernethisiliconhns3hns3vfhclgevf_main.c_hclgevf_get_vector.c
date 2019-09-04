#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct hnae3_vector_info {int /*<<< orphan*/  vector; scalar_t__ io_addr; } ;
struct hnae3_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ io_base; } ;
struct hclgevf_dev {int num_msi_left; int num_msi; scalar_t__* vector_status; int num_msi_used; int /*<<< orphan*/ * vector_irq; TYPE_1__ hw; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ HCLGEVF_INVALID_VPORT ; 
 int HCLGEVF_MISC_VECTOR_NUM ; 
 scalar_t__ HCLGEVF_VECTOR_REG_BASE ; 
 int HCLGEVF_VECTOR_REG_OFFSET ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_get_vector(struct hnae3_handle *handle, u16 vector_num,
			      struct hnae3_vector_info *vector_info)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hnae3_vector_info *vector = vector_info;
	int alloc = 0;
	int i, j;

	vector_num = min(hdev->num_msi_left, vector_num);

	for (j = 0; j < vector_num; j++) {
		for (i = HCLGEVF_MISC_VECTOR_NUM + 1; i < hdev->num_msi; i++) {
			if (hdev->vector_status[i] == HCLGEVF_INVALID_VPORT) {
				vector->vector = pci_irq_vector(hdev->pdev, i);
				vector->io_addr = hdev->hw.io_base +
					HCLGEVF_VECTOR_REG_BASE +
					(i - 1) * HCLGEVF_VECTOR_REG_OFFSET;
				hdev->vector_status[i] = 0;
				hdev->vector_irq[i] = vector->vector;

				vector++;
				alloc++;

				break;
			}
		}
	}
	hdev->num_msi_left -= alloc;
	hdev->num_msi_used += alloc;

	return alloc;
}