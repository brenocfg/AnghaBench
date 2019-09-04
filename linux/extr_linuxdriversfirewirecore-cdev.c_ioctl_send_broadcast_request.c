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
struct fw_cdev_send_request {int tcode; scalar_t__ offset; } ;
union ioctl_arg {struct fw_cdev_send_request send_request; } ;
struct client {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSR_CONFIG_ROM_END ; 
 scalar_t__ CSR_REGISTER_BASE ; 
 int EACCES ; 
 int EINVAL ; 
 int LOCAL_BUS ; 
 int /*<<< orphan*/  SCODE_100 ; 
#define  TCODE_WRITE_BLOCK_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int init_request (struct client*,struct fw_cdev_send_request*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_send_broadcast_request(struct client *client,
					union ioctl_arg *arg)
{
	struct fw_cdev_send_request *a = &arg->send_request;

	switch (a->tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
	case TCODE_WRITE_BLOCK_REQUEST:
		break;
	default:
		return -EINVAL;
	}

	/* Security policy: Only allow accesses to Units Space. */
	if (a->offset < CSR_REGISTER_BASE + CSR_CONFIG_ROM_END)
		return -EACCES;

	return init_request(client, a, LOCAL_BUS | 0x3f, SCODE_100);
}