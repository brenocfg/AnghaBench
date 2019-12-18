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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int NFP_CPP_ID (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_CPP_ID_ACTION_of (int) ; 
 int NFP_CPP_ID_ISLAND_of (int) ; 
 int NFP_CPP_ID_TARGET_of (int) ; 
 int /*<<< orphan*/  NFP_CPP_ID_TOKEN_of (int) ; 
 int nfp_cppat_addr_encode (int /*<<< orphan*/ *,int const,int const,int,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int const) ; 

int nfp_target_cpp(u32 cpp_island_id, u64 cpp_island_address,
		   u32 *cpp_target_id, u64 *cpp_target_address,
		   const u32 *imb_table)
{
	const int island = NFP_CPP_ID_ISLAND_of(cpp_island_id);
	const int target = NFP_CPP_ID_TARGET_of(cpp_island_id);
	u32 imb;
	int err;

	if (target < 0 || target >= 16) {
		pr_err("Invalid CPP target: %d\n", target);
		return -EINVAL;
	}

	if (island == 0) {
		/* Already translated */
		*cpp_target_id = cpp_island_id;
		*cpp_target_address = cpp_island_address;
		return 0;
	}

	/* CPP + Island only allowed on systems with IMB tables */
	if (!imb_table)
		return -EINVAL;

	imb = imb_table[target];

	*cpp_target_address = cpp_island_address;
	err = nfp_cppat_addr_encode(cpp_target_address, island, target,
				    ((imb >> 13) & 7), ((imb >> 12) & 1),
				    ((imb >> 6)  & 0x3f), ((imb >> 0)  & 0x3f));
	if (err) {
		pr_err("Can't encode CPP address: %d\n", err);
		return err;
	}

	*cpp_target_id = NFP_CPP_ID(target,
				    NFP_CPP_ID_ACTION_of(cpp_island_id),
				    NFP_CPP_ID_TOKEN_of(cpp_island_id));

	return 0;
}