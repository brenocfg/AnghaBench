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
typedef  int /*<<< orphan*/  u16 ;
struct enic {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENIC_DEVCMD_PROXY_BY_INDEX (int,int,struct enic*,int /*<<< orphan*/ ,int*) ; 
#define  ERR_EBADSTATE 135 
#define  ERR_EINPROGRESS 134 
#define  ERR_EINVAL 133 
#define  ERR_ENOMEM 132 
#define  ERR_SUCCESS 131 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_BADSTATE ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_ERROR ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_INPROGRESS ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_INVALID ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_SUCCESS ; 
#define  PORT_REQUEST_ASSOCIATE 130 
#define  PORT_REQUEST_DISASSOCIATE 129 
#define  PORT_REQUEST_PREASSOCIATE_RR 128 
 int /*<<< orphan*/  vnic_dev_deinit_done ; 
 int /*<<< orphan*/  vnic_dev_enable2_done ; 

int enic_process_get_pp_request(struct enic *enic, int vf,
	int request, u16 *response)
{
	int err, status = ERR_SUCCESS;

	switch (request) {

	case PORT_REQUEST_PREASSOCIATE_RR:
	case PORT_REQUEST_ASSOCIATE:
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
			vnic_dev_enable2_done, &status);
		break;

	case PORT_REQUEST_DISASSOCIATE:
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
			vnic_dev_deinit_done, &status);
		break;

	default:
		return -EINVAL;
	}

	if (err)
		status = err;

	switch (status) {
	case ERR_SUCCESS:
		*response = PORT_PROFILE_RESPONSE_SUCCESS;
		break;
	case ERR_EINVAL:
		*response = PORT_PROFILE_RESPONSE_INVALID;
		break;
	case ERR_EBADSTATE:
		*response = PORT_PROFILE_RESPONSE_BADSTATE;
		break;
	case ERR_ENOMEM:
		*response = PORT_PROFILE_RESPONSE_INSUFFICIENT_RESOURCES;
		break;
	case ERR_EINPROGRESS:
		*response = PORT_PROFILE_RESPONSE_INPROGRESS;
		break;
	default:
		*response = PORT_PROFILE_RESPONSE_ERROR;
		break;
	}

	return 0;
}