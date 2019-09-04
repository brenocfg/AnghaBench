#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tcode; } ;
union ioctl_arg {TYPE_2__ send_request; } ;
struct client {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TCODE_LOCK_BOUNDED_ADD 138 
#define  TCODE_LOCK_COMPARE_SWAP 137 
#define  TCODE_LOCK_FETCH_ADD 136 
#define  TCODE_LOCK_LITTLE_ADD 135 
#define  TCODE_LOCK_MASK_SWAP 134 
#define  TCODE_LOCK_VENDOR_DEPENDENT 133 
#define  TCODE_LOCK_WRAP_ADD 132 
#define  TCODE_READ_BLOCK_REQUEST 131 
#define  TCODE_READ_QUADLET_REQUEST 130 
#define  TCODE_WRITE_BLOCK_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int init_request (struct client*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_send_request(struct client *client, union ioctl_arg *arg)
{
	switch (arg->send_request.tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
	case TCODE_WRITE_BLOCK_REQUEST:
	case TCODE_READ_QUADLET_REQUEST:
	case TCODE_READ_BLOCK_REQUEST:
	case TCODE_LOCK_MASK_SWAP:
	case TCODE_LOCK_COMPARE_SWAP:
	case TCODE_LOCK_FETCH_ADD:
	case TCODE_LOCK_LITTLE_ADD:
	case TCODE_LOCK_BOUNDED_ADD:
	case TCODE_LOCK_WRAP_ADD:
	case TCODE_LOCK_VENDOR_DEPENDENT:
		break;
	default:
		return -EINVAL;
	}

	return init_request(client, &arg->send_request, client->device->node_id,
			    client->device->max_speed);
}