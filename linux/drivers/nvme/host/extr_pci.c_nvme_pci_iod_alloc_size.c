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
struct scatterlist {int dummy; } ;
struct nvme_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int nvme_npages (unsigned int,struct nvme_dev*) ; 
 int nvme_pci_npages_sgl (unsigned int) ; 

__attribute__((used)) static unsigned int nvme_pci_iod_alloc_size(struct nvme_dev *dev,
		unsigned int size, unsigned int nseg, bool use_sgl)
{
	size_t alloc_size;

	if (use_sgl)
		alloc_size = sizeof(__le64 *) * nvme_pci_npages_sgl(nseg);
	else
		alloc_size = sizeof(__le64 *) * nvme_npages(size, dev);

	return alloc_size + sizeof(struct scatterlist) * nseg;
}