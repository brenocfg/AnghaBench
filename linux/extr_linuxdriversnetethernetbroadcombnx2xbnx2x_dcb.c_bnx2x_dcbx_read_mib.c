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
typedef  scalar_t__ u32 ;
struct lldp_remote_mib {scalar_t__ prefix_seq_num; scalar_t__ suffix_seq_num; } ;
struct lldp_local_mib {scalar_t__ prefix_seq_num; scalar_t__ suffix_seq_num; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 scalar_t__ BP_PORT (struct bnx2x*) ; 
 int DCBX_LOCAL_MIB_MAX_TRY_READ ; 
#define  DCBX_READ_LOCAL_MIB 129 
#define  DCBX_READ_REMOTE_MIB 128 
 int /*<<< orphan*/  bnx2x_read_data (struct bnx2x*,scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int bnx2x_dcbx_read_mib(struct bnx2x *bp,
			       u32 *base_mib_addr,
			       u32 offset,
			       int read_mib_type)
{
	int max_try_read = 0;
	u32 mib_size, prefix_seq_num, suffix_seq_num;
	struct lldp_remote_mib *remote_mib ;
	struct lldp_local_mib  *local_mib;

	switch (read_mib_type) {
	case DCBX_READ_LOCAL_MIB:
		mib_size = sizeof(struct lldp_local_mib);
		break;
	case DCBX_READ_REMOTE_MIB:
		mib_size = sizeof(struct lldp_remote_mib);
		break;
	default:
		return 1; /*error*/
	}

	offset += BP_PORT(bp) * mib_size;

	do {
		bnx2x_read_data(bp, base_mib_addr, offset, mib_size);

		max_try_read++;

		switch (read_mib_type) {
		case DCBX_READ_LOCAL_MIB:
			local_mib = (struct lldp_local_mib *) base_mib_addr;
			prefix_seq_num = local_mib->prefix_seq_num;
			suffix_seq_num = local_mib->suffix_seq_num;
			break;
		case DCBX_READ_REMOTE_MIB:
			remote_mib = (struct lldp_remote_mib *) base_mib_addr;
			prefix_seq_num = remote_mib->prefix_seq_num;
			suffix_seq_num = remote_mib->suffix_seq_num;
			break;
		default:
			return 1; /*error*/
		}
	} while ((prefix_seq_num != suffix_seq_num) &&
	       (max_try_read < DCBX_LOCAL_MIB_MAX_TRY_READ));

	if (max_try_read >= DCBX_LOCAL_MIB_MAX_TRY_READ) {
		BNX2X_ERR("MIB could not be read\n");
		return 1;
	}

	return 0;
}