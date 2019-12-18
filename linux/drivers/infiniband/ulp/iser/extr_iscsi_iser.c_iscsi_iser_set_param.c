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
struct iscsi_cls_conn {int dummy; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int EPROTO ; 
#define  ISCSI_PARAM_DATADGST_EN 132 
#define  ISCSI_PARAM_HDRDGST_EN 131 
#define  ISCSI_PARAM_IFMARKER_EN 130 
#define  ISCSI_PARAM_MAX_RECV_DLENGTH 129 
#define  ISCSI_PARAM_OFMARKER_EN 128 
 int iscsi_set_param (struct iscsi_cls_conn*,int,char*,int) ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 

__attribute__((used)) static int
iscsi_iser_set_param(struct iscsi_cls_conn *cls_conn,
		     enum iscsi_param param, char *buf, int buflen)
{
	int value;

	switch (param) {
	case ISCSI_PARAM_MAX_RECV_DLENGTH:
		/* TBD */
		break;
	case ISCSI_PARAM_HDRDGST_EN:
		sscanf(buf, "%d", &value);
		if (value) {
			iser_err("DataDigest wasn't negotiated to None\n");
			return -EPROTO;
		}
		break;
	case ISCSI_PARAM_DATADGST_EN:
		sscanf(buf, "%d", &value);
		if (value) {
			iser_err("DataDigest wasn't negotiated to None\n");
			return -EPROTO;
		}
		break;
	case ISCSI_PARAM_IFMARKER_EN:
		sscanf(buf, "%d", &value);
		if (value) {
			iser_err("IFMarker wasn't negotiated to No\n");
			return -EPROTO;
		}
		break;
	case ISCSI_PARAM_OFMARKER_EN:
		sscanf(buf, "%d", &value);
		if (value) {
			iser_err("OFMarker wasn't negotiated to No\n");
			return -EPROTO;
		}
		break;
	default:
		return iscsi_set_param(cls_conn, param, buf, buflen);
	}

	return 0;
}