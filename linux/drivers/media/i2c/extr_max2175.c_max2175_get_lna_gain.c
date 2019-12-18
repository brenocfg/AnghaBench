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
typedef  int u32 ;
struct max2175 {int dummy; } ;
typedef  enum max2175_band { ____Placeholder_max2175_band } max2175_band ;

/* Variables and functions */
#define  MAX2175_BAND_AM 130 
#define  MAX2175_BAND_FM 129 
#define  MAX2175_BAND_VHF 128 
 int max2175_read_bits (struct max2175*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 max2175_get_lna_gain(struct max2175 *ctx)
{
	enum max2175_band band = max2175_read_bits(ctx, 5, 1, 0);

	switch (band) {
	case MAX2175_BAND_AM:
		return max2175_read_bits(ctx, 51, 3, 0);
	case MAX2175_BAND_FM:
		return max2175_read_bits(ctx, 50, 3, 0);
	case MAX2175_BAND_VHF:
		return max2175_read_bits(ctx, 52, 5, 0);
	default:
		return 0;
	}
}