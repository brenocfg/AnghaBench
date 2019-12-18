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
struct nvm_dev {int /*<<< orphan*/  lun_map; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvm_reserve_luns(struct nvm_dev *dev, int lun_begin, int lun_end)
{
	int i;

	for (i = lun_begin; i <= lun_end; i++) {
		if (test_and_set_bit(i, dev->lun_map)) {
			pr_err("lun %d already allocated\n", i);
			goto err;
		}
	}

	return 0;
err:
	while (--i >= lun_begin)
		clear_bit(i, dev->lun_map);

	return -EBUSY;
}