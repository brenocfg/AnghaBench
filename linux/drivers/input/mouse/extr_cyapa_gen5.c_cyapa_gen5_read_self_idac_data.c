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
struct cyapa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN5_RETRIEVE_SELF_CAP_PWC_DATA ; 
 int /*<<< orphan*/  PIP_RETRIEVE_DATA_STRUCTURE ; 
 int cyapa_gen5_read_idac_data (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 

__attribute__((used)) static int cyapa_gen5_read_self_idac_data(struct cyapa *cyapa,
		int *gidac_self_rx, int *gidac_self_tx,
		int *lidac_self_max, int *lidac_self_min, int *lidac_self_ave)
{
	int data_size;
	int error;

	*gidac_self_rx = *gidac_self_tx = 0;
	*lidac_self_max = *lidac_self_min = *lidac_self_ave = 0;

	data_size = 0;
	error = cyapa_gen5_read_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_SELF_CAP_PWC_DATA,
		&data_size,
		lidac_self_max, lidac_self_min, lidac_self_ave);
	if (error)
		return error;
	*gidac_self_rx = *lidac_self_max;
	*gidac_self_tx = *lidac_self_min;

	error = cyapa_gen5_read_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_SELF_CAP_PWC_DATA,
		&data_size,
		lidac_self_max, lidac_self_min, lidac_self_ave);
	return error;
}