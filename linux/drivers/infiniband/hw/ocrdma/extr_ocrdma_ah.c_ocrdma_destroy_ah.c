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
typedef  int /*<<< orphan*/  u32 ;
struct ocrdma_dev {int dummy; } ;
struct ocrdma_ah {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct ocrdma_ah* get_ocrdma_ah (struct ib_ah*) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_free_av (struct ocrdma_dev*,struct ocrdma_ah*) ; 

void ocrdma_destroy_ah(struct ib_ah *ibah, u32 flags)
{
	struct ocrdma_ah *ah = get_ocrdma_ah(ibah);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibah->device);

	ocrdma_free_av(dev, ah);
}