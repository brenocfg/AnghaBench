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
typedef  int u32 ;
struct pt1 {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pt1_read_reg (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pt1_do_enable_ram(struct pt1 *pt1)
{
	int i, j;
	u32 status;
	status = pt1_read_reg(pt1, 0) & 0x00000004;
	pt1_write_reg(pt1, 0, 0x00000002);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 1024; j++) {
			if ((pt1_read_reg(pt1, 0) & 0x00000004) != status)
				return 0;
		}
		usleep_range(1000, 2000);
	}
	dev_err(&pt1->pdev->dev, "could not enable RAM\n");
	return -EIO;
}