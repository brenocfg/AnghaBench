#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntb_dev {TYPE_1__* msi; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_3__ {void (* desc_changed ) (void*) ;scalar_t__* peer_mws; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int ntb_peer_mw_count (struct ntb_dev*) ; 
 int ntb_peer_mw_get_addr (struct ntb_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_peer_port_count (struct ntb_dev*) ; 

int ntb_msi_init(struct ntb_dev *ntb,
		 void (*desc_changed)(void *ctx))
{
	phys_addr_t mw_phys_addr;
	resource_size_t mw_size;
	size_t struct_size;
	int peer_widx;
	int peers;
	int ret;
	int i;

	peers = ntb_peer_port_count(ntb);
	if (peers <= 0)
		return -EINVAL;

	struct_size = sizeof(*ntb->msi) + sizeof(*ntb->msi->peer_mws) * peers;

	ntb->msi = devm_kzalloc(&ntb->dev, struct_size, GFP_KERNEL);
	if (!ntb->msi)
		return -ENOMEM;

	ntb->msi->desc_changed = desc_changed;

	for (i = 0; i < peers; i++) {
		peer_widx = ntb_peer_mw_count(ntb) - 1 - i;

		ret = ntb_peer_mw_get_addr(ntb, peer_widx, &mw_phys_addr,
					   &mw_size);
		if (ret)
			goto unroll;

		ntb->msi->peer_mws[i] = devm_ioremap(&ntb->dev, mw_phys_addr,
						     mw_size);
		if (!ntb->msi->peer_mws[i]) {
			ret = -EFAULT;
			goto unroll;
		}
	}

	return 0;

unroll:
	for (i = 0; i < peers; i++)
		if (ntb->msi->peer_mws[i])
			devm_iounmap(&ntb->dev, ntb->msi->peer_mws[i]);

	devm_kfree(&ntb->dev, ntb->msi);
	ntb->msi = NULL;
	return ret;
}