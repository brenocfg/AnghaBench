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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvm_release_luns_err(struct nvm_dev *dev, int lun_begin,
				 int lun_end)
{
	int i;

	for (i = lun_begin; i <= lun_end; i++)
		WARN_ON(!test_and_clear_bit(i, dev->lun_map));
}