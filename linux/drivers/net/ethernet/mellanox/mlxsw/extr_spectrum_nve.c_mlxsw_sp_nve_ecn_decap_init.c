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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int INET_ECN_CE ; 
 int INET_ECN_NOT_ECT ; 
 int __mlxsw_sp_nve_ecn_decap_init (struct mlxsw_sp*,int,int) ; 

__attribute__((used)) static int mlxsw_sp_nve_ecn_decap_init(struct mlxsw_sp *mlxsw_sp)
{
	int i;

	/* Iterate over inner ECN values */
	for (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) {
		int j;

		/* Iterate over outer ECN values */
		for (j = INET_ECN_NOT_ECT; j <= INET_ECN_CE; j++) {
			int err;

			err = __mlxsw_sp_nve_ecn_decap_init(mlxsw_sp, i, j);
			if (err)
				return err;
		}
	}

	return 0;
}