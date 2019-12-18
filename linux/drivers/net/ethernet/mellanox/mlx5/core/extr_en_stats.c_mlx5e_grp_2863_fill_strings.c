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
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_PPORT_2863_COUNTERS ; 
 TYPE_1__* pport_2863_stats_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_grp_2863_fill_strings(struct mlx5e_priv *priv, u8 *data,
				       int idx)
{
	int i;

	for (i = 0; i < NUM_PPORT_2863_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN, pport_2863_stats_desc[i].format);
	return idx;
}