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
typedef  size_t u32 ;
struct nfp_app_bpf {int dummy; } ;
struct cmsg_reply_map_simple {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  CMSG_RC_ERR_MAP_E2BIG 142 
#define  CMSG_RC_ERR_MAP_ERR 141 
#define  CMSG_RC_ERR_MAP_EXIST 140 
#define  CMSG_RC_ERR_MAP_FD 139 
#define  CMSG_RC_ERR_MAP_NOENT 138 
#define  CMSG_RC_ERR_MAP_NOMEM 137 
#define  CMSG_RC_ERR_MAP_PARSE 136 
#define  CMSG_RC_SUCCESS 135 
#define  E2BIG 134 
#define  EBADFD 133 
#define  EEXIST 132 
#define  EINVAL 131 
#define  EIO 130 
#define  ENOENT 129 
#define  ENOMEM 128 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,size_t) ; 

__attribute__((used)) static int
nfp_bpf_ctrl_rc_to_errno(struct nfp_app_bpf *bpf,
			 struct cmsg_reply_map_simple *reply)
{
	static const int res_table[] = {
		[CMSG_RC_SUCCESS]	= 0,
		[CMSG_RC_ERR_MAP_FD]	= -EBADFD,
		[CMSG_RC_ERR_MAP_NOENT]	= -ENOENT,
		[CMSG_RC_ERR_MAP_ERR]	= -EINVAL,
		[CMSG_RC_ERR_MAP_PARSE]	= -EIO,
		[CMSG_RC_ERR_MAP_EXIST]	= -EEXIST,
		[CMSG_RC_ERR_MAP_NOMEM]	= -ENOMEM,
		[CMSG_RC_ERR_MAP_E2BIG]	= -E2BIG,
	};
	u32 rc;

	rc = be32_to_cpu(reply->rc);
	if (rc >= ARRAY_SIZE(res_table)) {
		cmsg_warn(bpf, "FW responded with invalid status: %u\n", rc);
		return -EIO;
	}

	return res_table[rc];
}