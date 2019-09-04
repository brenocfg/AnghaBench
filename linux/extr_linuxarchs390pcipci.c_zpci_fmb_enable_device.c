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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct zpci_fib {int /*<<< orphan*/  fmb_addr; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int fmb_length; int /*<<< orphan*/ * fmb; int /*<<< orphan*/  unmapped_pages; int /*<<< orphan*/  mapped_pages; int /*<<< orphan*/  allocated_pages; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_SET_MEASURE ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zdev_fmb_cache ; 
 scalar_t__ zpci_mod_fc (int,struct zpci_fib*,scalar_t__*) ; 

int zpci_fmb_enable_device(struct zpci_dev *zdev)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_SET_MEASURE);
	struct zpci_fib fib = {0};
	u8 cc, status;

	if (zdev->fmb || sizeof(*zdev->fmb) < zdev->fmb_length)
		return -EINVAL;

	zdev->fmb = kmem_cache_zalloc(zdev_fmb_cache, GFP_KERNEL);
	if (!zdev->fmb)
		return -ENOMEM;
	WARN_ON((u64) zdev->fmb & 0xf);

	/* reset software counters */
	atomic64_set(&zdev->allocated_pages, 0);
	atomic64_set(&zdev->mapped_pages, 0);
	atomic64_set(&zdev->unmapped_pages, 0);

	fib.fmb_addr = virt_to_phys(zdev->fmb);
	cc = zpci_mod_fc(req, &fib, &status);
	if (cc) {
		kmem_cache_free(zdev_fmb_cache, zdev->fmb);
		zdev->fmb = NULL;
	}
	return cc ? -EIO : 0;
}