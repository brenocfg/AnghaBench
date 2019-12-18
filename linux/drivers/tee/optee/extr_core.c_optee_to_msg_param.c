#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  shm; } ;
struct TYPE_7__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_9__ {TYPE_3__ memref; TYPE_2__ value; } ;
struct tee_param {int attr; TYPE_4__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_10__ {TYPE_1__ value; } ;
struct optee_msg_param {int attr; TYPE_5__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPTEE_MSG_ATTR_TYPE_VALUE_INPUT ; 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT 134 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT 133 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT 132 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_NONE 131 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT 130 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT 129 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT 128 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tee_shm_is_registered (int /*<<< orphan*/ ) ; 
 int to_msg_param_reg_mem (struct optee_msg_param*,struct tee_param const*) ; 
 int to_msg_param_tmp_mem (struct optee_msg_param*,struct tee_param const*) ; 

int optee_to_msg_param(struct optee_msg_param *msg_params, size_t num_params,
		       const struct tee_param *params)
{
	int rc;
	size_t n;

	for (n = 0; n < num_params; n++) {
		const struct tee_param *p = params + n;
		struct optee_msg_param *mp = msg_params + n;

		switch (p->attr) {
		case TEE_IOCTL_PARAM_ATTR_TYPE_NONE:
			mp->attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
			memset(&mp->u, 0, sizeof(mp->u));
			break;
		case TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			mp->attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT + p->attr -
				   TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT;
			mp->u.value.a = p->u.value.a;
			mp->u.value.b = p->u.value.b;
			mp->u.value.c = p->u.value.c;
			break;
		case TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			if (tee_shm_is_registered(p->u.memref.shm))
				rc = to_msg_param_reg_mem(mp, p);
			else
				rc = to_msg_param_tmp_mem(mp, p);
			if (rc)
				return rc;
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}