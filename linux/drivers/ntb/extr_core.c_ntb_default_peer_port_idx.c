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
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NTB_DEF_PEER_IDX ; 
 int ntb_default_peer_port_number (struct ntb_dev*,int /*<<< orphan*/ ) ; 

int ntb_default_peer_port_idx(struct ntb_dev *ntb, int port)
{
	int peer_port = ntb_default_peer_port_number(ntb, NTB_DEF_PEER_IDX);

	if (peer_port == -EINVAL || port != peer_port)
		return -EINVAL;

	return 0;
}