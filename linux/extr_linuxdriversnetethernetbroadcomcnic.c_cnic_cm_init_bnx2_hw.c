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
struct cnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cnic_ctx_wr (struct cnic_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_u32 () ; 

__attribute__((used)) static int cnic_cm_init_bnx2_hw(struct cnic_dev *dev)
{
	u32 seed;

	seed = prandom_u32();
	cnic_ctx_wr(dev, 45, 0, seed);
	return 0;
}