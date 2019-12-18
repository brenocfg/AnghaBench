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
struct TYPE_2__ {int /*<<< orphan*/  lp; } ;
struct vnet_port {TYPE_1__ vio; } ;
struct vio_net_desc {int dummy; } ;
struct vio_dring_state {int entry_size; int /*<<< orphan*/  ncookies; int /*<<< orphan*/  cookies; } ;

/* Variables and functions */
 int ldc_put_dring_entry (int /*<<< orphan*/ ,struct vio_net_desc*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int put_rx_desc(struct vnet_port *port,
		       struct vio_dring_state *dr,
		       struct vio_net_desc *desc,
		       u32 index)
{
	int err;

	err = ldc_put_dring_entry(port->vio.lp, desc, dr->entry_size,
				  (index * dr->entry_size),
				  dr->cookies, dr->ncookies);
	if (err < 0)
		return err;

	return 0;
}