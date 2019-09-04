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
struct hclge_vport {int vport_id; struct hclge_dev* back; } ;
struct TYPE_2__ {scalar_t__ io_base; } ;
struct hclge_dev {int num_msi_left; int num_msi; int* vector_status; int num_msi_used; int /*<<< orphan*/ * vector_irq; TYPE_1__ hw; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int HCLGE_INVALID_VPORT ; 
 scalar_t__ HCLGE_VECTOR_REG_BASE ; 
 int HCLGE_VECTOR_REG_OFFSET ; 
 int HCLGE_VECTOR_VF_OFFSET ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_get_vector(struct hnae3_handle *handle, u16 vector_num,
			    struct hnae3_vector_info *vector_info)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hnae3_vector_info *vector = vector_info;
	struct hclge_dev *hdev = vport->back;
	int alloc = 0;
	int i, j;

	vector_num = min(hdev->num_msi_left, vector_num);

	for (j = 0; j < vector_num; j++) {
		for (i = 1; i < hdev->num_msi; i++) {
			if (hdev->vector_status[i] == HCLGE_INVALID_VPORT) {
				vector->vector = pci_irq_vector(hdev->pdev, i);
				vector->io_addr = hdev->hw.io_base +
					HCLGE_VECTOR_REG_BASE +
					(i - 1) * HCLGE_VECTOR_REG_OFFSET +
					vport->vport_id *
					HCLGE_VECTOR_VF_OFFSET;
				hdev->vector_status[i] = vport->vport_id;
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