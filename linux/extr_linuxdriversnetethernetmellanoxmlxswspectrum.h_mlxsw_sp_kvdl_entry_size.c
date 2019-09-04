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
typedef  enum mlxsw_sp_kvdl_entry_type { ____Placeholder_mlxsw_sp_kvdl_entry_type } mlxsw_sp_kvdl_entry_type ;

/* Variables and functions */
#define  MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET 131 
#define  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ 130 
#define  MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR 129 
#define  MLXSW_SP_KVDL_ENTRY_TYPE_PBS 128 

__attribute__((used)) static inline unsigned int
mlxsw_sp_kvdl_entry_size(enum mlxsw_sp_kvdl_entry_type type)
{
	switch (type) {
	case MLXSW_SP_KVDL_ENTRY_TYPE_ADJ: /* fall through */
	case MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET: /* fall through */
	case MLXSW_SP_KVDL_ENTRY_TYPE_PBS: /* fall through */
	case MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR: /* fall through */
	default:
		return 1;
	}
}