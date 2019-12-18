#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_PME_ERR_STATS ; 
 int NUM_PME_STATUS_STATS ; 
 TYPE_2__* mlx5e_pme_error_desc ; 
 TYPE_1__* mlx5e_pme_status_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_grp_pme_fill_strings(struct mlx5e_priv *priv, u8 *data,
				      int idx)
{
	int i;

	for (i = 0; i < NUM_PME_STATUS_STATS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN, mlx5e_pme_status_desc[i].format);

	for (i = 0; i < NUM_PME_ERR_STATS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN, mlx5e_pme_error_desc[i].format);

	return idx;
}