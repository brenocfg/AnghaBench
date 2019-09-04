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
typedef  int /*<<< orphan*/  u8 ;
struct vmbuspipe_hdr {int dummy; } ;
struct icmsg_negotiate {int icframe_vercnt; int icmsg_vercnt; TYPE_1__* icversion_data; } ;
struct icmsg_hdr {int icmsgsize; } ;
struct TYPE_2__ {int major; int minor; } ;

/* Variables and functions */

bool vmbus_prep_negotiate_resp(struct icmsg_hdr *icmsghdrp,
				u8 *buf, const int *fw_version, int fw_vercnt,
				const int *srv_version, int srv_vercnt,
				int *nego_fw_version, int *nego_srv_version)
{
	int icframe_major, icframe_minor;
	int icmsg_major, icmsg_minor;
	int fw_major, fw_minor;
	int srv_major, srv_minor;
	int i, j;
	bool found_match = false;
	struct icmsg_negotiate *negop;

	icmsghdrp->icmsgsize = 0x10;
	negop = (struct icmsg_negotiate *)&buf[
		sizeof(struct vmbuspipe_hdr) +
		sizeof(struct icmsg_hdr)];

	icframe_major = negop->icframe_vercnt;
	icframe_minor = 0;

	icmsg_major = negop->icmsg_vercnt;
	icmsg_minor = 0;

	/*
	 * Select the framework version number we will
	 * support.
	 */

	for (i = 0; i < fw_vercnt; i++) {
		fw_major = (fw_version[i] >> 16);
		fw_minor = (fw_version[i] & 0xFFFF);

		for (j = 0; j < negop->icframe_vercnt; j++) {
			if ((negop->icversion_data[j].major == fw_major) &&
			    (negop->icversion_data[j].minor == fw_minor)) {
				icframe_major = negop->icversion_data[j].major;
				icframe_minor = negop->icversion_data[j].minor;
				found_match = true;
				break;
			}
		}

		if (found_match)
			break;
	}

	if (!found_match)
		goto fw_error;

	found_match = false;

	for (i = 0; i < srv_vercnt; i++) {
		srv_major = (srv_version[i] >> 16);
		srv_minor = (srv_version[i] & 0xFFFF);

		for (j = negop->icframe_vercnt;
			(j < negop->icframe_vercnt + negop->icmsg_vercnt);
			j++) {

			if ((negop->icversion_data[j].major == srv_major) &&
				(negop->icversion_data[j].minor == srv_minor)) {

				icmsg_major = negop->icversion_data[j].major;
				icmsg_minor = negop->icversion_data[j].minor;
				found_match = true;
				break;
			}
		}

		if (found_match)
			break;
	}

	/*
	 * Respond with the framework and service
	 * version numbers we can support.
	 */

fw_error:
	if (!found_match) {
		negop->icframe_vercnt = 0;
		negop->icmsg_vercnt = 0;
	} else {
		negop->icframe_vercnt = 1;
		negop->icmsg_vercnt = 1;
	}

	if (nego_fw_version)
		*nego_fw_version = (icframe_major << 16) | icframe_minor;

	if (nego_srv_version)
		*nego_srv_version = (icmsg_major << 16) | icmsg_minor;

	negop->icversion_data[0].major = icframe_major;
	negop->icversion_data[0].minor = icframe_minor;
	negop->icversion_data[1].major = icmsg_major;
	negop->icversion_data[1].minor = icmsg_minor;
	return found_match;
}