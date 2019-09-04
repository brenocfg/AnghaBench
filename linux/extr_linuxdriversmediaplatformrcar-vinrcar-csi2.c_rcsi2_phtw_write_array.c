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
struct rcar_csi2 {int dummy; } ;
struct phtw_value {scalar_t__ code; scalar_t__ data; } ;

/* Variables and functions */
 int rcsi2_phtw_write (struct rcar_csi2*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rcsi2_phtw_write_array(struct rcar_csi2 *priv,
				  const struct phtw_value *values)
{
	const struct phtw_value *value;
	int ret;

	for (value = values; value->data || value->code; value++) {
		ret = rcsi2_phtw_write(priv, value->data, value->code);
		if (ret)
			return ret;
	}

	return 0;
}