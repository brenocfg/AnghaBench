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
struct mlx5_flow_steering {TYPE_1__* sniffer_rx_root_ns; } ;
struct fs_prio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FS_FT_SNIFFER_RX ; 
 scalar_t__ IS_ERR (struct fs_prio*) ; 
 int PTR_ERR (struct fs_prio*) ; 
 int /*<<< orphan*/  cleanup_root_ns (TYPE_1__*) ; 
 TYPE_1__* create_root_ns (struct mlx5_flow_steering*,int /*<<< orphan*/ ) ; 
 struct fs_prio* fs_create_prio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_sniffer_rx_root_ns(struct mlx5_flow_steering *steering)
{
	struct fs_prio *prio;

	steering->sniffer_rx_root_ns = create_root_ns(steering, FS_FT_SNIFFER_RX);
	if (!steering->sniffer_rx_root_ns)
		return -ENOMEM;

	/* Create single prio */
	prio = fs_create_prio(&steering->sniffer_rx_root_ns->ns, 0, 1);
	if (IS_ERR(prio)) {
		cleanup_root_ns(steering->sniffer_rx_root_ns);
		return PTR_ERR(prio);
	}
	return 0;
}