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
struct phtw_value {int data; int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  phtw_mbps_h3_v3h_m3n ; 
 int rcsi2_phtw_write (struct rcar_csi2*,int,int) ; 
 int rcsi2_phtw_write_array (struct rcar_csi2*,struct phtw_value const*) ; 
 int rcsi2_phtw_write_mbps (struct rcar_csi2*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __rcsi2_init_phtw_h3_v3h_m3n(struct rcar_csi2 *priv,
					unsigned int mbps)
{
	static const struct phtw_value step1[] = {
		{ .data = 0xcc, .code = 0xe2 },
		{ .data = 0x01, .code = 0xe3 },
		{ .data = 0x11, .code = 0xe4 },
		{ .data = 0x01, .code = 0xe5 },
		{ .data = 0x10, .code = 0x04 },
		{ /* sentinel */ },
	};

	static const struct phtw_value step2[] = {
		{ .data = 0x38, .code = 0x08 },
		{ .data = 0x01, .code = 0x00 },
		{ .data = 0x4b, .code = 0xac },
		{ .data = 0x03, .code = 0x00 },
		{ .data = 0x80, .code = 0x07 },
		{ /* sentinel */ },
	};

	int ret;

	ret = rcsi2_phtw_write_array(priv, step1);
	if (ret)
		return ret;

	if (mbps != 0 && mbps <= 250) {
		ret = rcsi2_phtw_write(priv, 0x39, 0x05);
		if (ret)
			return ret;

		ret = rcsi2_phtw_write_mbps(priv, mbps, phtw_mbps_h3_v3h_m3n,
					    0xf1);
		if (ret)
			return ret;
	}

	return rcsi2_phtw_write_array(priv, step2);
}