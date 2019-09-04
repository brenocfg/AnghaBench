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
struct pvrdma_dev {int /*<<< orphan*/  cq_pdir; } ;
struct pvrdma_cqne {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ pvrdma_page_dir_get_ptr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline struct pvrdma_cqne *get_cqne(struct pvrdma_dev *dev,
					   unsigned int i)
{
	return (struct pvrdma_cqne *)pvrdma_page_dir_get_ptr(
					&dev->cq_pdir,
					PAGE_SIZE +
					sizeof(struct pvrdma_cqne) * i);
}