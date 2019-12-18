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
typedef  enum mlxsw_core_reg_access_type { ____Placeholder_mlxsw_core_reg_access_type } mlxsw_core_reg_access_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MLXSW_CORE_REG_ACCESS_TYPE_QUERY 129 
#define  MLXSW_CORE_REG_ACCESS_TYPE_WRITE 128 

__attribute__((used)) static inline const char *
mlxsw_core_reg_access_type_str(enum mlxsw_core_reg_access_type type)
{
	switch (type) {
	case MLXSW_CORE_REG_ACCESS_TYPE_QUERY:
		return "query";
	case MLXSW_CORE_REG_ACCESS_TYPE_WRITE:
		return "write";
	}
	BUG();
}