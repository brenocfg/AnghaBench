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
struct nct6775_data {int* temp_src; int /*<<< orphan*/ * REG_TEMP_SOURCE; } ;

/* Variables and functions */
 int ENODEV ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_temp_source(struct nct6775_data *data, int index, int count)
{
	int source = data->temp_src[index];
	int nr;

	for (nr = 0; nr < count; nr++) {
		int src;

		src = nct6775_read_value(data,
					 data->REG_TEMP_SOURCE[nr]) & 0x1f;
		if (src == source)
			return nr;
	}
	return -ENODEV;
}